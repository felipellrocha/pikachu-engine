#include "collision.h"

void CollisionSystem::update(float dt) {
  auto entities = manager->getAllEntitiesWithComponent<CollisionComponent>();

  for (auto& ref1 : entities) {
    EID e1 = ref1.first;

    auto c1 = manager->getComponent<CollisionComponent>(e1);
    auto p1 = manager->getComponent<PositionComponent>(e1);

    if (c1->isStatic) continue;

    // cleaning up
    for (EID e2 : c1->collisions) {
      auto c2 = manager->getComponent<CollisionComponent>(e2);
      auto p2 = manager->getComponent<PositionComponent>(e2);

      if (!c2 || !p2) {
        queue.push_front(e2);
        continue;
      }

      int x1 = p1->x + c1->x;
      int y1 = p1->y + c1->y;
      int x2 = p2->x + c2->x;
      int y2 = p2->y + c2->y;

      bool collidingX = isOverlapping(x1, x1 + c1->w, x2, x2 + c2->w);
      bool collidingY = isOverlapping(y1, y1 + c1->h, y2, y2 + c2->h);
      bool colliding = collidingX && collidingY;

      if (!colliding) {
        queue.push_front(e2);
      }
    }

    for (EID e2 : queue) {
      c1->collisions.erase(e2);
    }

    queue.clear();

    for (auto& ref2 : entities) {
      EID e2 = ref2.first;

      auto c2 = manager->getComponent<CollisionComponent>(e2);
      auto p2 = manager->getComponent<PositionComponent>(e2);

      if (!c2 || !p2 || e1 == e2 || damageResolverComplement(c1, c2)) {
        p1->y = p1->nextY;
        p1->x = p1->nextX;
        continue;
      }

      int x1 = p1->nextX + c1->x;
      int y1 = p1->nextY + c1->y;
      int x2 = p2->nextX + c2->x;
      int y2 = p2->nextY + c2->y;

      bool collidingX = isOverlapping(x1, x1 + c1->w, x2, x2 + c2->w);
      bool collidingY = isOverlapping(y1, y1 + c1->h, y2, y2 + c2->h);
      bool colliding = collidingX && collidingY;

      // resolve movements
      if (colliding) {
        if (c2->onCollision != nullptr && c1->collisions.find(e2) == c1->collisions.end()) {
          game->runScript(c2->onCollision);
        }
        c1->collisions.insert(e2);

        if (wallResolver(c1, c2)) {
          // resolve movements
          int h_distance = abs((x1 + c1->w / 2) - (x2 + c2->w / 2));
          int v_distance = abs((y1 + c1->h / 2) - (y2 + c2->h / 2));

          if (v_distance > h_distance) {
            int overlap = calculateOverlap(y1, y1 + c1->h,  y2, y2 + c2->h);
            int direction = (Compass::NORTH & p1->direction) ? 1 : -1;
            p1->nextY += direction * overlap;
          }
          else if (h_distance > v_distance) {
            int overlap = calculateOverlap(x1, x1 + c1->w, x2, x2 + c2->w);
            int direction = (Compass::EAST & p1->direction) ? -1 : 1;
            p1->nextX += direction * overlap;
          }
        }

        if (damageResolver(c1, c2)) {
          manager->removeEntity(e1);
          c2->collisions.erase(e1);

          auto health = manager->getComponent<HealthComponent>(e2);

          if (health) {
            health->currentHearts -= 1;
            if (health->currentHearts < 0) {
              manager->removeEntity(e2);
              c1->collisions.erase(e2);
            }
          }
        }
      }

      c1->isColliding = c1->isColliding || colliding;

      p1->y = p1->nextY;
      p1->x = p1->nextX;
    }
  }
};

bool CollisionSystem::wallResolver(CollisionComponent* c1, CollisionComponent* c2) {
  return (
    (c1->resolver & Resolver::CHARACTER && c2->resolver & Resolver::WALL) ||
    (c2->resolver & Resolver::CHARACTER && c1->resolver & Resolver::WALL) ||
    (c2->resolver & Resolver::CHARACTER && c1->resolver & Resolver::CHARACTER)
  );
};

bool CollisionSystem::damageResolver(CollisionComponent* c1, CollisionComponent* c2) {
  return c1->resolver & Resolver::ATTACK && c2->resolver & Resolver::CHARACTER;
};

bool CollisionSystem::damageResolverComplement(CollisionComponent* c1, CollisionComponent* c2) {
  return c1->resolver & Resolver::CHARACTER && c2->resolver & Resolver::ATTACK;
};

#include "input.h"

void InputSystem::update(float dt) {
  auto entities = manager->getAllEntitiesWithComponent<InputComponent>();
  for (auto& ref : entities) {
    EID entity = ref.first;

    auto movement = manager->getComponent<MovementComponent>(entity);
    auto position = manager->getComponent<PositionComponent>(entity);
    auto walk = manager->getComponent<WalkComponent>(entity);

    position->direction = this->game->compass;

    if (Compass::NORTH & this->game->compass) {
      position->nextY -= (Actions::SECONDARY & this->game->actions) ? movement->fast.y : movement->slow.y;
      if (walk) {
        walk->direction = Compass::NORTH;
        walk->animating = true;
      }
    }
    if (Compass::EAST & this->game->compass) {
      position->nextX += (Actions::SECONDARY & this->game->actions) ? movement->fast.x : movement->slow.x;
      if (walk) {
        walk->direction = Compass::EAST;
        walk->animating = true;
      }
    }
    if (Compass::SOUTH & this->game->compass) {
      position->nextY += (Actions::SECONDARY & this->game->actions) ? movement->fast.y : movement->slow.y;
      if (walk) {
        walk->direction = Compass::SOUTH;
        walk->animating = true;
      }
    }
    if (Compass::WEST & this->game->compass) {
      position->nextX -= (Actions::SECONDARY & this->game->actions) ? movement->fast.x : movement->slow.x;
      if (walk) {
        walk->direction = Compass::WEST;
        walk->animating = true;
      }
    }

    if (walk && this->game->compass == 0) {
      walk->animating = false;
    }
  }
};


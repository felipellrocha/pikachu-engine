#include "ability.h"

void AbilitySystem::update(float dt) {
  auto entities = manager->getAllEntitiesWithComponent<AbilityComponent>();

  for (auto& ref : entities) {
    EID entity = ref.first;

    auto abilities = manager->getComponent<AbilityComponent>(entity);
    auto walk = manager->getComponent<WalkComponent>(entity);
    auto render = manager->getComponent<RenderComponent>(entity);
    auto position = manager->getComponent<PositionComponent>(entity);

    if (Actions::ATTACK1 & this->game->actions && abilities->abilities[Actions::ATTACK1]) {
      Ability* ability = abilities->abilities[Actions::ATTACK1];
      if (ability->delay > ability->threshold) {
        int direction = 0;
        int xOffset = 0;
        int yOffset = 0;

        if (Compass::NORTH & walk->direction) {
          direction = Compass::NORTH;
          yOffset = -48;
        }
        if (Compass::EAST & walk->direction) {
          direction = Compass::EAST;
          xOffset = 48;
        }
        if (Compass::SOUTH & walk->direction) {
          direction = Compass::SOUTH;
          yOffset = 48;
        }
        if (Compass::WEST & walk->direction) {
          direction = Compass::WEST;
          xOffset = -48;
        }

        EID attack = this->manager->createEntity();

        manager->addComponent<RenderComponent>(attack, render->layer, false, false);
        manager->addComponent<DimensionComponent>(attack, 48, 48);

        manager->addComponent<CollisionComponent>(attack,
          false,
          Resolver::ATTACK,
          12, 12, 24, 24
        );
        manager->addComponent<PositionComponent>(
          attack,
          position->x + xOffset,
          position->y + yOffset,
          direction
        );
        manager->addComponent<SpriteComponent>(
          attack,
          0, 0, 48, 48,
          this->game->textures["flame"]
        );
        if (ability->type == AbilityType::RANGE) manager->addComponent<ProjectileComponent>(attack, 8);

        ability->delay = 0.f;
      }
      ability->delay += dt;
    }
  }
};

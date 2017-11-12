#include "projectile.h"

void ProjectileSystem::update(float dt) {
  auto entities = manager->getAllEntitiesWithComponent<ProjectileComponent>();

  for (auto& ref : entities) {
    EID entity = ref.first;
    
    auto projectile = manager->getComponent<ProjectileComponent>(entity);
    auto position = manager->getComponent<PositionComponent>(entity);

    if (Compass::NORTH & position->direction) position->nextY -= projectile->vec; 
    if (Compass::EAST & position->direction) position->nextX += projectile->vec; 
    if (Compass::SOUTH & position->direction) position->nextY += projectile->vec; 
    if (Compass::WEST & position->direction) position->nextX -= projectile->vec;
  }

};


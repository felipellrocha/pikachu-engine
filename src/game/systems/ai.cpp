#include "ai.h"

void AISystem::update(float dt) {
  auto entities = manager->getAllEntitiesWithComponent<AIComponent>();

  for (auto& item : entities) {
    EID entity = item.first;

    game->behaviors[entity]->update();
  }
};


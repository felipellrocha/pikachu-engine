#include "change-map.h"

void FadeOutTransition::begin(EntityManager* manager, Renderer* game) {
  this->entity = manager->createEntity();
  manager->addComponent<PositionComponent>(entity, 0, 0);
  manager->addComponent<DimensionComponent>(entity, game->windowWidth, game->windowHeight);
  manager->addComponent<ColorComponent>(entity, 0, 0, 0, 0);
  manager->addComponent<RenderComponent>(entity, 999);

  EID player = manager->getSpecial("player");
  manager->removeComponent<InputComponent>(player);
  auto render = manager->getComponent<RenderComponent>(player);
  render->layer = 1000;
};

bool FadeOutTransition::tick(EntityManager* manager, Renderer* game, float dt) {
  if (step == 0) {
    auto color = manager->getComponent<ColorComponent>(entity);
    color->a = (int)((running / duration) * 255);

    running += dt;

    if (running > duration) {
      running = 0.f;
      step += 1;
    }
    
    return false;
  }
  else if (step == 1) {
    manager->clear();
    string level = game->mapsByName[mapName];
    game->loadStage(level);


    this->entity = manager->createEntity();
    manager->addComponent<PositionComponent>(entity, 0, 0);
    manager->addComponent<DimensionComponent>(entity, game->windowWidth, game->windowHeight);
    manager->addComponent<ColorComponent>(entity, 0, 0, 0, 255);
    manager->addComponent<RenderComponent>(entity, 999);

    step += 1;
    
    return false;
  }
  else if (step == 2) {
    auto color = manager->getComponent<ColorComponent>(entity);
    color->a = 255 - (int)((running / duration) * 255);

    running += dt;

    if (running > duration) {
      running = 0.f;
      step += 1;
    }

    return false;
  }
  else {
    return true;
  }
};

Transition* FadeOutTransition::end(EntityManager* manager, Renderer* game) {
  EID player = manager->getSpecial("player");
  manager->addComponent<InputComponent>(player);

  return NULL;
};

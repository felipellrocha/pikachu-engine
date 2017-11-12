#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>

#include "entity.h"

class Renderer;
class System {
  public:
    EntityManager *manager;
    Renderer *game;

    System(EntityManager *_manager, Renderer *_game)
      : manager(_manager), game(_game) {};
    virtual void update(float dt) =0;
};

#endif

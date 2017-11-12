#ifndef SYSTEMINPUT_H
#define SYSTEMINPUT_H

#include "sdl2image.h"
#include "game/components.h"

#include "renderer/compass.h"
#include "renderer/renderer.h"

#include "entity/entity.h"
#include "entity/system.h"

class InputSystem : public System {
  public:
    void update(float dt);

    InputSystem(EntityManager *_manager, Renderer *_game) :
      System(_manager, _game) { };
};

#endif

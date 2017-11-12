#ifndef SYSTEMWALK_H
#define SYSTEMWALK_H

#include "sdl2image.h"
#include "game/components.h"

#include "renderer/compass.h"
#include "renderer/animation.h"
#include "renderer/renderer.h"

#include "entity/entity.h"
#include "entity/system.h"

class WalkSystem : public System {
  public:
    void update(float dt);

    WalkSystem(EntityManager *_manager, Renderer *_game) :
      System(_manager, _game) { };
};

#endif

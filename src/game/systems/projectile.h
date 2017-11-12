#ifndef SYSTEMPROJECTILE_H
#define SYSTEMPROJECTILE_H

#include "sdl2image.h"
#include "game/components.h"
#include "game/utils.h"

#include "renderer/compass.h"
#include "renderer/renderer.h"

#include "entity/entity.h"
#include "entity/system.h"
#include "game/transitions/change-map.h"

class ProjectileSystem : public System {
  public:
    float timing = 2.f;

    void update(float dt);

    ProjectileSystem(EntityManager *_manager, Renderer *_game) :
      System(_manager, _game) { };
};

#endif

#ifndef SYSTEMCAMERA_H
#define SYSTEMCAMERA_H

#include "sdl2image.h"

#include "game/components.h"

#include "renderer/compass.h"
#include "renderer/renderer.h"

#include "entity/entity.h"
#include "entity/system.h"

using namespace std;

class CameraSystem : public System {
  public:
    void update(float dt);

    CameraSystem(EntityManager *_manager, Renderer *_game) :
      System(_manager, _game) { };
};

#endif

#ifndef SYSTEMTRANSITION_H
#define SYSTEMTRANSITION_H

#include <vector>
#include "sdl2image.h"

#include "game/components.h"

#include "renderer/compass.h"
#include "renderer/renderer.h"

#include "entity/entity.h"
#include "entity/system.h"

using namespace std;

class TransitionSystem : public System {
  public:

    void update(float dt);

    TransitionSystem(EntityManager *_manager, Renderer *_game) :
      System(_manager, _game) { };
};

#endif


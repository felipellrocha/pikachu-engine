#ifndef SYSTEMAI_H
#define SYSTEMAI_H

#include "sdl2image.h"

#include "game/components.h"

#include "renderer/renderer.h"

#include "entity/entity.h"
#include "entity/system.h"

#include "game/behaviors/follow.h"

using namespace std;

class AISystem : public System {
public:
  void update(float dt);

  AISystem(EntityManager *_manager, Renderer *_game) :
  System(_manager, _game) { };

  ~AISystem() { }
};

#endif

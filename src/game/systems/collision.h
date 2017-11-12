#ifndef SYSTEMCOLLISION_H
#define SYSTEMCOLLISION_H

#include "sdl2image.h"
#include <cstdlib>
#include <forward_list>

#include "game/components.h"
#include "game/utils.h"

#include "renderer/renderer.h"
#include "renderer/compass.h"

#include "entity/entity.h"
#include "entity/system.h"

using namespace std;

class CollisionSystem : public System {
public:
  void update(float dt);

  forward_list<EID> queue;

  bool wallResolver(CollisionComponent* c1, CollisionComponent* c2);
  bool damageResolver(CollisionComponent* c1, CollisionComponent* c2);
  bool damageResolverComplement(CollisionComponent* c1, CollisionComponent* c2);

  CollisionSystem(EntityManager *_manager, Renderer *_game) :
    System(_manager, _game) { };
};

#endif

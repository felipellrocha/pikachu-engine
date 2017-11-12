#ifndef TRANSITION_H
#define TRANSITION_H

#include "entity/entity.h"
#include "renderer/renderer.h"

typedef uint32_t TID;

class Transition {
  public:
    TID id;

    virtual void begin(EntityManager* manager, Renderer* game) { };
    virtual bool tick(EntityManager* manager, Renderer* game, float dt) =0;
    virtual Transition* end(EntityManager* manager, Renderer* game) { return NULL; };

    bool operator<(Transition const &other) const {
      return id < other.id;
    }
};

#endif

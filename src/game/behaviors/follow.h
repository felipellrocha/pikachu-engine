#ifndef FOLLOW_H
#define FOLLOW_H

#include "AI/leaf.h"

class Follower : public Leaf {
public:
  Follower(Renderer* _game, EntityManager* _manager, EID _owner) :
    Leaf(_game, _manager, _owner) { };

  Status update() override;
};

#endif

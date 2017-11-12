#ifndef PROXIMITY_H
#define PROXIMITY_H

#include "AI/leaf.h"

class Proximity : public Leaf {
public:
  int distance = 0;

  Proximity(Renderer* _game, EntityManager* _manager, EID _owner, int _distance) :
    Leaf(_game, _manager, _owner) {
      distance = _distance * _distance;
    };

  Status update() override;
};

#endif

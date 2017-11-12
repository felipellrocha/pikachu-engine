#ifndef LEAF_H
#define LEAF_H

#include "node.h"
#include "game/components.h"

class Leaf : public Node {
public:
  Leaf(Renderer* _game, EntityManager* _manager, EID _owner) :
    Node(_game, _manager, _owner) { };

  virtual Status update() =0;
};

#endif

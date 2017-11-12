#ifndef BEHAVIORTREE_H
#define BEHAVIORTREE_H

#include "node.h"

class BehaviorTree : public Node {
public:
  Node* root = nullptr;

  Status update() { return root->tick(); }
  void setRoot (Node* node) { root = node; }

  BehaviorTree(Renderer* _game, EntityManager* _manager, EID _owner) :
    Node(_game, _manager, _owner) { };

  ~BehaviorTree() {
    delete root;
    root = nullptr;
  }
};

#endif

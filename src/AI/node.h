#ifndef NODE_H
#define NODE_H

#include <vector>
#include "entity/entity.h"

enum Status {
  INVALID,
  SUCCESS,
  FAILURE,
  RUNNING,
  ERROR,
};

class Renderer;
class Node {
public:

  Status status = Status::INVALID;
  Renderer* game;
  EntityManager* manager;
  EID owner;

  Node(Renderer* _game, EntityManager* _manager, EID _owner) :
    game(_game), manager(_manager), owner(_owner) { };

  virtual ~Node() {};

  virtual Status update() =0;
  virtual void initialize() {}
  virtual void terminate(Status s) {};

  Status tick() {
    if (status != Status::RUNNING) initialize();
    status = update();
    if (status != Status::RUNNING) terminate(status);

    return status;
  }

  bool isSuccess() { return status == Status::SUCCESS; }
  bool isFailure() { return status == Status::FAILURE; }
  bool isRunning() { return status == Status::RUNNING; }
  bool isTerminated() { return status == Status::SUCCESS || status == Status::FAILURE; }

  void reset() { status = Status::INVALID; }
};

typedef vector<Node*> Nodes;

#endif

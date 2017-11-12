#ifndef DECORATOR_H
#define DECORATOR_H

#include "node.h"

class Decorator : public Node {
public:
  Node* child = nullptr;

  void setChild(Node* _child) { child = _child; }
  bool hasNoChild() const { return child == nullptr; }

  Decorator(Renderer* _game, EntityManager* _manager, EID _owner) :
    Node(_game, _manager, _owner) { };

  ~Decorator() {
    delete child;
  }
};

class Failer : public Decorator {
public:
  Failer(Renderer* _game, EntityManager* _manager, EID _owner) :
    Decorator(_game, _manager, _owner) { };

  Status update() override {
    child->tick();
    return Status::FAILURE;
  }
};

class Succeeder : public Decorator {
public:
  Succeeder(Renderer* _game, EntityManager* _manager, EID _owner) :
    Decorator(_game, _manager, _owner) { };

  Status update() override {
    child->tick();
    return Status::SUCCESS;
  }
};

class Inverter : public Decorator {
public:
  Inverter(Renderer* _game, EntityManager* _manager, EID _owner) :
    Decorator(_game, _manager, _owner) { };

  Status update() override {
    auto status = child->tick();

    if (status == Status::SUCCESS) return Status::FAILURE;
    else if (status == Status::FAILURE) return Status::SUCCESS;

    return status;
  }
};

class Repeater : public Decorator {
public:
  int limit = 0;
  int counter = 0;

  Repeater(Renderer* _game, EntityManager* _manager, EID _owner, int _limit) :
    Decorator(_game, _manager, _owner), limit(_limit) { };

  void initialize() override { counter = 0; }

  Status update() override {
    while (true) {
      auto status = child->tick();

      if (status == Status::RUNNING) return Status::RUNNING;
      if (status == Status::FAILURE) return Status::FAILURE;
      if (limit > 0 && ++counter == limit) return Status::SUCCESS;

      child->reset();
    }
  }
};

class untilFail : public Decorator {
public:
  untilFail(Renderer* _game, EntityManager* _manager, EID _owner) :
    Decorator(_game, _manager, _owner) { };

  Status update() override {
    while (true) {
      auto status = child->tick();

      if (status == Status::FAILURE) return Status::SUCCESS;
    }
  }
};

class untilSuccess : public Decorator {
public:
  untilSuccess(Renderer* _game, EntityManager* _manager, EID _owner) :
    Decorator(_game, _manager, _owner) { };

  Status update() override {
    while (true) {
      auto status = child->tick();

      if (status == Status::SUCCESS) return Status::SUCCESS;
    }
  }
};

#endif

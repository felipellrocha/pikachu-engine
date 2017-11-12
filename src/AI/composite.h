#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "node.h"

class Composite : public Node {
public:
  Nodes children;
  int index = 0;

  void addChild(Node* child) { children.push_back(child); }
  bool hasNoChildren() const { return children.empty(); }

  Composite(Renderer* _game, EntityManager* _manager, EID _owner) :
    Node(_game, _manager, _owner) { };

  ~Composite() {
    for (auto& child : children) {
      delete child;
    }
    children.clear();
  }
};

class Parallel : public Composite {
public:
  bool useSuccessFailPolicy = false;
  bool successOnAll = true;
  bool failOnAll = true;
  int minSuccess = 0;
  int minFail = 0;

  Parallel(Renderer* _game, EntityManager* _manager, EID _owner, bool _successOnAll = true, bool _failOnAll = true) :
    Composite(_game, _manager, _owner), useSuccessFailPolicy(true), successOnAll(_successOnAll), failOnAll(_failOnAll) { };
  Parallel(Renderer* _game, EntityManager* _manager, EID _owner, int _minSuccess, int _minFail) :
    Composite(_game, _manager, _owner), minSuccess(_minSuccess), minFail(_minFail) { };

  Status update() override {
    int minimumSuccess = minSuccess;
    int minimumFail = minFail;

    if (useSuccessFailPolicy) {
      if (successOnAll) minimumSuccess = children.size();
      else minimumSuccess = 1;

      if (failOnAll) minimumFail = children.size();
      else minimumFail = 1;
    }

    int totalSuccess = 0;
    int totalFail = 0;

    for (auto& child : children) {
      auto status = child->tick();

      if (status == Status::SUCCESS) totalSuccess++;
      if (status == Status::FAILURE) totalFail++;
    }

    if (totalSuccess >= minimumSuccess) return Status::SUCCESS;
    if (totalFail >= minimumFail) return Status::FAILURE;

    return Status::RUNNING;
  }
};

class MemSequence : public Composite {
public:
  MemSequence(Renderer* _game, EntityManager* _manager, EID _owner) :
    Composite(_game, _manager, _owner) { };

  Status update() override {
    if (hasNoChildren()) return Status::SUCCESS;

    for (auto& child : children) {
      auto status = child->tick();

      if (status != Status::SUCCESS) return status;
    }

    return Status::SUCCESS;
  }
};

class Sequence : public Composite {
public:
  Sequence(Renderer* _game, EntityManager* _manager, EID _owner) :
    Composite(_game, _manager, _owner) { };

  void initialize() override { index = 0; }

  Status update() override {
    if (hasNoChildren()) return Status::SUCCESS;

    for (auto& child : children) {
      auto status = child->tick();

      if (status != Status::SUCCESS) return status;
    }

    return Status::SUCCESS;
  }
};

class MemSelector : public Composite {
public:
  MemSelector(Renderer* _game, EntityManager* _manager, EID _owner) :
    Composite(_game, _manager, _owner) { };

  Status update() override {
    if (hasNoChildren()) return Status::SUCCESS;

    while (true) {
      auto& child = children.at(index);
      auto status = child->tick();

      if (status != Status::FAILURE) return status;

      if (++index == children.size()) return Status::FAILURE;
    }
  }
};

class Selector : public Composite {
public:
  Selector(Renderer* _game, EntityManager* _manager, EID _owner) :
    Composite(_game, _manager, _owner) { };

  void initialize() override { index = 0; }

  Status update() override {
    if (hasNoChildren()) return Status::SUCCESS;

    while (true) {
      auto& child = children.at(index);
      auto status = child->tick();

      if (status != Status::FAILURE) return status;

      if (++index == children.size()) return Status::FAILURE;
    }
  }
};

#endif

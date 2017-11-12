#include "entity.h"

EID EntityManager::getSpecial(string key) {
  return this->special[key];
}

void EntityManager::saveSpecial(string key, EID entity) {
  this->special[key] = entity;
}

EID EntityManager::generateEid() {
  return lowestUnassignedEid++;
}

EID EntityManager::createEntity() {
  EID eid = generateEid();

  return eid;
}

void EntityManager::removeEntity(EID eid) {
  for (auto& it : components) {
    auto cid = it.first;

    if (components[cid].count(eid)) {
      auto entity = components[cid][eid];
      components[cid].erase(eid);
      delete entity;
    }
  }
}

void EntityManager::clear() {
  for (auto& type : components) {
    for (auto& component : type.second) {
      delete component.second;
    }
    components[type.first].clear();
  }

  special.clear();
}

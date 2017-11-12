#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <vector>
#include <string>
#include <array>
#include <map>

#include "entity/component.h"

using namespace std;

typedef uint32_t EID;

struct Entity {
  EID eid;

  Entity(EID _eid) : eid(_eid) {}
};

class EntityManager {
  public:
    int lowestUnassignedEid = 0;
    map<type_index, map<EID, Component *>> components;
    map<string, EID> special;

    EID getSpecial(string key);
    void saveSpecial(string key, EID entity);

    EID generateEid();
    EID createEntity();
    void removeEntity(EID eid);
    void clear();

    ~EntityManager() {
      this->clear();
    }

    template<class ComponentClass, typename... Args>
    ComponentClass* addComponent(EID entity, Args... args) {
      ComponentClass* component = new ComponentClass(args...);
      type_index cid = type_index(typeid(ComponentClass));
      components[cid][entity] = component;
      return component;
    }

    template<class ComponentClass>
    void removeComponent(EID eid) {
      type_index cid = type_index(typeid(ComponentClass));
      if (components[cid].find(eid) == components[cid].end()) return;

      components[cid].erase(eid);
    }

    template<class ComponentClass>
    ComponentClass* getComponent(EID eid) {
      type_index cid = type_index(typeid(ComponentClass));
      if (components.find(cid) == components.end()) return nullptr;
      if (components[cid].find(eid) == components[cid].end()) return nullptr;

      auto component = components[cid][eid];

      return static_cast<ComponentClass *>(component);
    }

    template<class ComponentClass>
    map<EID, Component *> getAllEntitiesWithComponent() {
      vector<EID> entities;
      type_index cid = type_index(typeid(ComponentClass));

      return components[cid];
      /*for (auto& component : components[cid]) {
        entities.push_back(component.first);
      }*/

      //return entities;
    }
};

#endif

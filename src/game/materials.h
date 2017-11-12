#ifndef MATERIAL_H
#define MATERIAL_H

enum AbilityType {
  MELEE,
  RANGE,
  BODY,
};

enum ElementType {
  FIRE,
  WATER,
  EARTH,
  WIND,
  ELECTRIC,
  METAL,
};

enum Resolver {
  CHARACTER = 2,
  ATTACK = 4,
  WALL = 8,
};

struct Ability {
  AbilityType type;
  ElementType element;

  float delay = 0.f;
  float threshold;
  int penalty;

  Ability(AbilityType _type, ElementType _element, float _threshold, int _penalty) :
    type(_type), element(_element), threshold(_threshold), penalty(_penalty) { };
};


#endif

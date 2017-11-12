#ifndef GAMECOMPONENTS_H
#define GAMECOMPONENTS_H

#include "sdl2image.h"
#include <string>
#include <iostream>
#include <set>
#include <map>

#include "json/json.h"
#include "renderer/compass.h"
#include "entity/entity.h"
#include "entity/component.h"
#include "game/utils.h"
#include "game/materials.h"
#include "renderer/geometry.h"
#include "renderer/compass.h"

using json = nlohmann::json;

typedef string TextureSource;
typedef json script;
typedef int ResolverType;
typedef map<Actions, Ability*> AbilityList;

struct HealthComponent : public Component {
  int currentHearts;
  int maxHearts;
  int currentEnergy;
  int maxEnergy;

  HealthComponent(int _ch, int _mh, int _ce, int _me)
    : currentHearts(_ch), maxHearts(_mh), currentEnergy(_ce), maxEnergy(_me) {}
};

struct AbilityComponent : public Component {

  AbilityList abilities;

  AbilityComponent() { };

  template<typename... Args>
  void makeAbility(Actions action, Args... args) {
    if (abilities[action]) delete abilities[action];
    Ability* ability = new Ability(args...);

    abilities[action] = ability;
  };
};

struct PositionComponent : public Component {
  int x; //private
  int y; //private

  int nextX; //private
  int nextY; //private

  int direction = 0; //private

  void move(int x, int y) {
    nextX = x;
    nextY = y;
  };

  PositionComponent(int _x, int _y)
    : x(_x), y(_y), nextX(_x), nextY(_y) { }
  PositionComponent(int _x, int _y, int _direction)
    : x(_x), y(_y), nextX(_x), nextY(_y), direction(_direction) { }
};

struct DimensionComponent : public Component {
  int w; //private
  int h; //private

  DimensionComponent(int _w, int _h) : w(_w), h(_h) {}
};

struct SpriteComponent : public Component {
  int x;
  int y;
  int w;
  int h;
  TextureSource src;
  SDL_Texture *texture; //private

  SpriteComponent(int _x, int _y, int _w, int _h, SDL_Texture* _texture)
      : x(_x), y(_y), w(_w), h(_h), texture(_texture) {
  }
};

struct InputComponent : public Component {
  InputComponent() {};
};

struct MovementComponent : public Component {
  point slow;
  point fast;

  MovementComponent(int sX = 0, int sY = 0, int fX = 0, int fY = 0) {
    slow = point(sX, sY);
    fast = point(fX, fY);
  };
};

struct RenderComponent : public Component {
  int layer; //private
  bool shouldTileX;
  bool shouldTileY;

  RenderComponent(int _layer, bool _shouldTileX, bool _shouldTileY)
  : layer(_layer), shouldTileX(_shouldTileX), shouldTileY(_shouldTileY) { };

  RenderComponent(int _layer)
  : layer(_layer), shouldTileX(false), shouldTileY(false) { };
};

struct CenteredCameraComponent : public Component {
  EID entity; //private

  CenteredCameraComponent(EID _entity) : entity(_entity) { };
};

struct CollisionComponent : public Component {
  // Static colliders are things like walls, and such, that are never moving
  // keeping track of them allows us to run a small optimization until we need
  // some more heavy duty things to check for collision

  bool isStatic = false;
  bool isColliding = false; //private
  ResolverType resolver;
  int x = 0;
  int y = 0;
  int w = 0;
  int h = 0;

	script onCollision = nullptr;

  set<EID> collisions; //private

  CollisionComponent(bool _isStatic, int _resolver, int _x, int _y, int _w, int _h)
    : isStatic(_isStatic),
      resolver(_resolver),
      x(_x),
      y(_y),
      w(_w),
      h(_h) { };
};

struct ProjectileComponent : public Component {
  int vec = 0;

  ProjectileComponent(int _vec)
    : vec(_vec) { };
};

struct WalkComponent : public Component {
  int direction = Compass::SOUTH; //private
  int frame; //private
  bool animating = false; //private

  WalkComponent(int _direction, int _frame) : direction(_direction), frame(_frame) { };
  WalkComponent(int _direction) : WalkComponent(_direction, 0) { };
  WalkComponent() : WalkComponent(0, 0) { };
};

struct ColorComponent : public Component {
  int r = 0;
  int g = 0;
  int b = 0;
  int a = 0;

  ColorComponent(int _r, int _g, int _b, int _a)
    : r(_r), g(_g), b(_b), a(_a) { };
};

struct ScriptComponent : public Component {
  bool onCollision = false;

  ScriptComponent() { };
};

struct AIComponent : public Component {

  AIComponent() { };
};

#endif

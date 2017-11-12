#ifndef CHANGE_MAP_TRANSITION
#define CHANGE_MAP_TRANSITION

#include <iostream>
#include "renderer/transition.h"
#include "game/components.h"

using namespace std;

class FadeOutTransition : public Transition {
  public:
		int step = 0;
    int x = 0;
    string mapName;
    float duration = .0f;
    float running = .0f;

		EID entity;
    
    FadeOutTransition (string _mapName, float _duration) :
      mapName(_mapName), duration(_duration) { };

    void begin(EntityManager* manager, Renderer* game);
    bool tick(EntityManager* manager, Renderer* game, float dt);
    Transition* end(EntityManager* manager, Renderer* game);
};

#endif

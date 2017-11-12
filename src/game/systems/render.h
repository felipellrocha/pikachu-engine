#ifndef SYSTEMRENDER_H
#define SYSTEMRENDER_H

#include "sdl2image.h"
#include "renderer/renderer.h"
#include "game/components.h"
#include "game/utils.h"

#include "entity/entity.h"
#include "entity/system.h"

#include "renderer/simpletile.h"
#include "renderer/fourtile.h"
#include "renderer/sixtile.h"

#include "renderer/shader.h"

struct RenderCacheItem {
  int layer;
  int y;
  EID entity;

  bool operator< (RenderCacheItem const &other) const;

  RenderCacheItem(int _layer, int _y, EID _entity)
    : layer(_layer), y(_y), entity(_entity) { };
};

class RenderSystem : public System {
  public:
    SDL_Color white = {255, 255, 255};
    SDL_Color black = {0, 0, 0};
    TTF_Font* font;
    TTF_Font* outline;
    SDL_Rect rect;

    set<RenderCacheItem> cache;

    SDL_Surface* bgSurface;
    SDL_Surface* fgSurface;
    SDL_Texture* message;

    //Shader testShader = Shader("assets/shaders/test.fragment.glsl");

    void update(float dt);

    RenderSystem(EntityManager* _manager, Renderer* _game) :
      System(_manager, _game) {
        /*
        font = TTF_OpenFont("assets/fonts/Verdana.ttf", 14);
        outline = TTF_OpenFont("assets/fonts/Verdana.ttf", 14);
        TTF_SetFontOutline(outline, 2);
         */
    };

    ~RenderSystem() {
      SDL_FreeSurface(bgSurface);
      SDL_FreeSurface(fgSurface);
    };
};

#endif

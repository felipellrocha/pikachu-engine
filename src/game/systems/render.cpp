#include "render.h"

void RenderSystem::update(float dt) {
  auto entities = manager->getAllEntitiesWithComponent<RenderComponent>(); 
  auto cameraPosition = manager->getComponent<PositionComponent>(manager->getSpecial("camera"));
  auto cameraDimension = manager->getComponent<DimensionComponent>(manager->getSpecial("camera"));

  SDL_Rect camera = {
    cameraPosition->x,
    cameraPosition->y,
    cameraDimension->w,
    cameraDimension->h,
  };

  SDL_SetRenderTarget(game->ren, game->texture);
  SDL_RenderClear(game->ren);

  for (auto& ref : entities) {
    EID entity = ref.first;
    auto render = manager->getComponent<RenderComponent>(entity);
    auto position = manager->getComponent<PositionComponent>(entity);

    int x = position->x;
    int y = position->y;

    bool overlappingX = isOverlapping(x, x + game->grid.tile_w, camera.x, camera.x + camera.w) || render->shouldTileX;
    bool overlappingY = isOverlapping(y, y + game->grid.tile_h, camera.y, camera.y + camera.h) || render->shouldTileY;
    bool colliding = overlappingX && overlappingY;

    if (!colliding) continue;

    RenderCacheItem c = RenderCacheItem(render->layer, position->y, entity);
    cache.insert(c);
  }

  for (auto &item : cache) {
    EID entity = item.entity;

    auto render = manager->getComponent<RenderComponent>(entity);
    auto sprite = manager->getComponent<SpriteComponent>(entity);
    auto position = manager->getComponent<PositionComponent>(entity);
    auto dimension = manager->getComponent<DimensionComponent>(entity);
    auto health = manager->getComponent<HealthComponent>(entity);
    auto color = manager->getComponent<ColorComponent>(entity);

    if (color) {
      SDL_SetRenderDrawColor( game->ren, color->r, color->g, color->b, color->a );
      SDL_Rect r;
      r.x = position->x;
      r.y = position->y;
      r.w = dimension->w;
      r.h = dimension->h;
      SDL_RenderFillRect(game->ren, &r);
    }

    else if (sprite) {
      if (render->shouldTileY && render->shouldTileX) {
        int xs = position->x - (ceil((float)position->x / sprite->w) * sprite->w);
        int ys = position->y - (ceil((float)position->y / sprite->h) * sprite->h);
        for (int x = xs; x + sprite->w < camera.w; x += sprite->w)
        for (int y = ys; y + sprite->h < camera.h; y += sprite->h) {
          SDL_Rect src = {
            sprite->x,
            sprite->y,
            sprite->w,
            sprite->h
          };

          SDL_Rect dst = {
            x - camera.x,
            y - camera.y,
            sprite->w,
            sprite->h
          };
          SDL_RenderCopy(game->ren, sprite->texture, &src, &dst);
        }
      }
      else if (render->shouldTileX) {
        int xs = position->x - (ceil((float)position->x / sprite->w) * sprite->w);
        for (int x = xs; x < camera.w; x += sprite->w) {
          SDL_Rect src = {
            sprite->x,
            sprite->y,
            sprite->w,
            sprite->h
          };

          SDL_Rect dst = {
            x - camera.x,
            position->y - camera.y,
            sprite->w,
            sprite->h
          };
          SDL_RenderCopy(game->ren, sprite->texture, &src, &dst);
        }
      }
      else if (render->shouldTileY) {
        int ys = position->y - (ceil((float)position->y / sprite->h) * sprite->h);
        for (int y = ys; y + sprite->h < camera.h; y += sprite->h) {
          SDL_Rect src = {
            sprite->x,
            sprite->y,
            sprite->w,
            sprite->h
          };

          SDL_Rect dst = {
            position->x - camera.x,
            y - camera.y,
            sprite->w,
            sprite->h
          };
          SDL_RenderCopy(game->ren, sprite->texture, &src, &dst);
        }
      }
      else {
        SDL_Rect src = {
          sprite->x,
          sprite->y,
          sprite->w,
          sprite->h
        };

        SDL_Rect dst = {
          position->x - camera.x,
          position->y - camera.y,
          sprite->w,
          sprite->h 
        };
        SDL_RenderCopy(game->ren, sprite->texture, &src, &dst);
      }
    }

    if (health) {
      string healthDisplay = to_string(health->currentHearts)
        + "/"
        + to_string(health->maxHearts);

      bgSurface = TTF_RenderText_Blended(outline, healthDisplay.c_str(), black);
      fgSurface = TTF_RenderText_Blended(font, healthDisplay.c_str(), white);
      message = SDL_CreateTextureFromSurface(game->ren, bgSurface);

      rect.w = bgSurface->w;
      rect.h = bgSurface->h;
      rect.x = position->x + (dimension->w / 2) - (rect.w / 2) - camera.x;
      rect.y = position->y - 17 - camera.y;

      SDL_RenderCopy(game->ren, message, NULL, &rect);
      SDL_FreeSurface(bgSurface);
      SDL_DestroyTexture(message);

      message = SDL_CreateTextureFromSurface(game->ren, fgSurface);

      rect.w = fgSurface->w;
      rect.h = fgSurface->h;
      rect.x = position->x + (dimension->w / 2) - (rect.w / 2) - camera.x;
      rect.y = position->y - 15 - camera.y;

      SDL_RenderCopy(game->ren, message, NULL, &rect);
      SDL_FreeSurface(fgSurface);
      SDL_DestroyTexture(message);
    }
  }

#ifdef DRAW_COLLISION
  entities = manager->getAllEntitiesWithComponent<CollisionComponent>();
  for (auto &item : entities) {
    EID entity = item.first;
    auto collision = manager->getComponent<CollisionComponent>(entity);
    auto position = manager->getComponent<PositionComponent>(entity);

    int x = position->x + collision->x;
    int y = position->y + collision->y;

    // Create a rectangle
    SDL_Rect r;
    r.x = x - camera.x;
    r.y = y - camera.y;
    r.w = collision->w;
    r.h = collision->h;

    SDL_SetRenderDrawColor( game->ren, 100, 255, 0, 200 );

    SDL_RenderDrawRect( game->ren, &r );
    /*

    EID entity = item.entity;
    auto collision = manager->getComponent<CollisionComponent>(entity);

    if (!collision) continue;

    auto position = manager->getComponent<PositionComponent>(entity);

    for (EID coll : collision->collisions) {
      auto c2 = manager->getComponent<CollisionComponent>(coll);
      auto p2 = manager->getComponent<PositionComponent>(coll);

      SDL_Rect r;
      r.x = p2->x + c2->x - camera.x;
      r.y = p2->y + c2->y - camera.y;
      r.w = c2->w;
      r.h = c2->h;

      SDL_SetRenderDrawColor( game->ren, 0, 255, 255, 200 );

      SDL_RenderDrawRect( game->ren, &r );

      SDL_RenderDrawLine(
        game->ren,
        position->x + collision->x + (collision->w / 2) - camera.x,
        position->y + collision->y + (collision->h / 2) - camera.y,
        p2->x + c2->x + (c2->w / 2) - camera.x,
        p2->y + c2->y + (c2->h / 2) - camera.y
      );
    }
    */
  }
#endif

#ifdef DRAW_FPS
	stringstream ss;
	ss << fixed << setprecision(2) << (1 / dt);
	string fpsString = ss.str();

	fgSurface = TTF_RenderText_Blended(font, fpsString.c_str(), white);

  message = SDL_CreateTextureFromSurface(game->ren, fgSurface);

  SDL_Rect rect;
  rect.w = fgSurface->w;
  rect.h = fgSurface->h;
  rect.x = 2;
  rect.y = 2;

  SDL_RenderCopy(game->ren, message, NULL, &rect);
#endif

  //testShader.use();

  cache.clear();
  SDL_SetRenderDrawColor( game->ren, 0, 0, 0, 0 );
  SDL_SetRenderTarget( game->ren, NULL );

  SDL_Rect transfer = {0, 0, cameraDimension->w, cameraDimension->h};

  SDL_RenderCopy(game->ren, game->texture, &transfer, &transfer);

  SDL_RenderPresent(game->ren);
};

bool RenderCacheItem::operator< (RenderCacheItem const &other) const {
  return tie(layer, y, entity) < tie(other.layer, other.y, other.entity);
}

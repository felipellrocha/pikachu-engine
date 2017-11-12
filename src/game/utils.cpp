#include "utils.h"

bool isOverlapping(int min1, int max1, int min2, int max2) {
  return max1 >= min2 && max2 >= min1;
}

int calculateOverlap(int min1, int max1, int min2, int max2) {
  return max(0, min(max1, max2) - max(min1, min2));
}

SDL_Texture* loadTexture(SDL_Renderer *ren, string src) {
  cout << ": Loading texture: " << src << endl;

  SDL_Texture *texture = IMG_LoadTexture(ren, src.c_str());
  if (texture == nullptr){
    std::cout << "x LoadTexture Error: " << src << " " << SDL_GetError() << std::endl;
    IMG_Quit();
    SDL_Quit();
    throw renderer_error();
  }

  return texture;
}

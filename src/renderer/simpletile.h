#ifndef SIMPLETILE_H
#define SIMPLETILE_H

#include <vector>
#include <array>
#include "sdl2image.h"
#include "renderer/compass.h"
#include "renderer/geometry.h"

using namespace std;

struct simpleTile {
  static vector<array<rect, 2>> calculateAll(int tileIndex, int locationIndex, Tileset *tileset, Grid* grid) {
    int width = grid->tile_w;
    int height = grid->tile_h;

    rect src = rect(
      (tileset->getX(tileIndex) * width),
      (tileset->getY(tileIndex) * height),
      width,
      height
    );
    rect dst = rect(
      (grid->getX(locationIndex) * width),
      (grid->getY(locationIndex) * height),
      width,
      height
    );

    return {{src, dst}};
  }
};

#endif

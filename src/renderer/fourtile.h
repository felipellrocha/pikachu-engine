#ifndef FOURTILE_H
#define FOURTILE_H

#include <array>
#include "sdl2image.h"
#include "renderer/compass.h"
#include "renderer/geometry.h"

using namespace std;

struct fourTile {
  static point southWestOffset(int surrounding) {
    if (Compass::SOUTH & surrounding
      && Compass::WEST & surrounding)
      return point(1, 2);

    if (Compass::SOUTH & surrounding)
      return point(0, 2);
    if (Compass::WEST & surrounding)
      return point(1, 3);

    return point(0, 3);
  }

  static point southEastOffset(int surrounding) {
    if (Compass::SOUTH & surrounding
      && Compass::EAST & surrounding)
      return point(2, 2);

    if (Compass::SOUTH & surrounding)
      return point(3, 2);
    if (Compass::EAST & surrounding)
      return point(2, 3);

    return point(3, 3);
  }

  static point northEastOffset(int surrounding) {
    if (Compass::NORTH & surrounding
      && Compass::EAST & surrounding)
      return point(2, 1);

    if (Compass::NORTH & surrounding)
      return point(3, 1);
    if (Compass::EAST & surrounding)
      return point(2, 0);

    return point(3, 0);
  }

  static point northWestOffset(int surrounding) {
    if (Compass::NORTH & surrounding
      && Compass::WEST & surrounding)
      return point(1, 1);

    if (Compass::NORTH & surrounding)
      return point(0, 1);
    if (Compass::WEST & surrounding)
      return point(1, 0);

    return point(0, 0);
  }

  static vector<array<rect, 2>> calculateAll(int tileIndex, int locationIndex, int surroundings, Tileset *tileset, Grid* grid) {
    int width = grid->tile_w / 2;
    int height = grid->tile_h / 2;

    auto calcs = calculateOffset(surroundings);
    vector<array<rect, 2>> out(4);

    for (int i = 0; i < 4; ++i) {
      point calc = calcs[i];

      rect src = rect(
        (tileset->getX(tileIndex) * grid->tile_w) + (calc.x * width),
        (tileset->getY(tileIndex) * grid->tile_h) + (calc.y * height),
        width,
        height
      );
      rect dst = rect(
        (grid->getX(locationIndex) * grid->tile_w) + ((i % 2) * width),
        (grid->getY(locationIndex) * grid->tile_h) + ((i / 2) * height),
        width,
        height
      );
      out[i] = {{src, dst}};
    }

    return out;
  }

  static array<point, 4> calculateOffset(int surrounding) {
    return {
      fourTile::northWestOffset(surrounding),
      fourTile::northEastOffset(surrounding),
      fourTile::southWestOffset(surrounding),
      fourTile::southEastOffset(surrounding)
    };
  }
};

#endif

#ifndef SIXTILE_H
#define SIXTILE_H

#include <vector>
#include <array>
#include "sdl2image.h"
#include "renderer/compass.h"
#include "renderer/geometry.h"

using namespace std;

struct sixTile {
  static point southWestOffset(int surrounding) {
    if (Compass::SOUTH & surrounding
      && Compass::WEST & surrounding
      && Compass::SOUTHWEST & surrounding)
      return point(1, 4);
    if (Compass::SOUTH & surrounding
      && Compass::WEST & surrounding)
      return point(2, 1);

    if (Compass::SOUTH & surrounding)
      return point(0, 4);
    if (Compass::WEST & surrounding)
      return point(1, 5);

    return point(0, 5);
  }

  static point southEastOffset(int surrounding) {
    if (Compass::SOUTH & surrounding
      && Compass::EAST & surrounding
      && Compass::SOUTHEAST & surrounding)
      return point(2, 4);
    if (Compass::SOUTH & surrounding
      && Compass::EAST & surrounding)
      return point(3, 1);

    if (Compass::SOUTH & surrounding)
      return point(3, 4);
    if (Compass::EAST & surrounding)
      return point(2, 5);

    return point(3, 5);
  }

  static point northEastOffset(int surrounding) {
    if (Compass::NORTH & surrounding
      && Compass::EAST & surrounding
      && Compass::NORTHEAST & surrounding)
      return point(2, 3);
    if (Compass::NORTH & surrounding
      && Compass::EAST & surrounding)
      return point(3, 0);

    if (Compass::NORTH & surrounding)
      return point(3, 3);
    if (Compass::EAST & surrounding)
      return point(2, 2);

    return point(3, 2);
  }

  static point northWestOffset(int surrounding) {
    if (Compass::NORTH & surrounding
      && Compass::WEST & surrounding
      && Compass::NORTHWEST & surrounding)
      return point(1, 3);
    if (Compass::NORTH & surrounding
      && Compass::WEST & surrounding)
      return point(2, 0);

    if (Compass::NORTH & surrounding)
      return point(0, 3);
    if (Compass::WEST & surrounding)
      return point(1, 2);

    return point(0, 2);
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
      sixTile::northWestOffset(surrounding),
      sixTile::northEastOffset(surrounding),
      sixTile::southWestOffset(surrounding),
      sixTile::southEastOffset(surrounding)
    };
  }
};

#endif

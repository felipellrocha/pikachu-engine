#ifndef TILE_H
#define TILE_H

#include "sdl2image.h"
#include <string>
#include "renderer/compass.h"
#include "renderer/tileset.h"

class Tile {
  public:
    int setIndex;
    int tileIndex;
    int locationIndex;
    int surrounding;

    Tile(int setIndex, int tileIndex, int locationIndex)
      : setIndex(setIndex), tileIndex(tileIndex), locationIndex(locationIndex) { }

    Tile()
      : Tile(0, 0, 0) { }

    bool operator== (Tile const &other) {
      return setIndex == other.setIndex && tileIndex == other.tileIndex;
    }
};

#endif

#ifndef TILESET_H
#define TILESET_H

#include <iostream>
#include "sdl2image.h"
#include "json/json.h"
#include "renderer/tile.h"

using json = nlohmann::json;
using namespace std;

class Grid {
  public:
    int rows = 0;
    int columns = 0;
    int tile_w = 0;
    int tile_h = 0;

    Grid(int rows, int columns) : rows(rows), columns(columns) {}
    Grid() : Grid(0, 0) { };

    friend ostream& operator<<(ostream &out, Grid const &grid) {
      out <<
        "<Grid " <<
        "rows(" << grid.rows << ") " <<
        "columns(" << grid.columns << ") " <<
        "Tile:w(" << grid.tile_w << ") " <<
        "Tile:h(" << grid.tile_h << ")" <<
        ">";

      return out;
    }

    int findSurroundings(json &t1, int i, json &data);

    bool isInside(int x, int y) {
      return x >= 0 && x < this->columns && y >= 0 && y < this->rows;
    }

    int getX(int index) {
      return index % this->columns;
    }

    int getY(int index) {
      return index / this->columns;
    }

    int getIndex(int x, int y) {
      return (y * this->columns) + x;
    }
};

class Tileset : public Grid {
  public:
    string type;
    SDL_Texture *texture = nullptr;
    map<int, string> terrains;

    friend ostream& operator<<(ostream &out, Tileset const &t) {
      out <<
        "<Tileset " <<
        "rows(" << t.rows << ") " <<
        "columns(" << t.columns << ") " <<
        "Tile:w(" << t.tile_w << ") " <<
        "Tile:h(" << t.tile_h << ") " <<
        "type(" << t.type << ")" <<
        ">";

      return out;
    }

    Tileset(int rows, int columns, string type, SDL_Texture *texture)
      : Grid(rows, columns), type(type), texture(texture) {}

    Tileset(int rows, int columns, string type, SDL_Texture *texture, map<int, string> terrains)
      : Grid(rows, columns), type(type), texture(texture), terrains(terrains) {}
};

#endif

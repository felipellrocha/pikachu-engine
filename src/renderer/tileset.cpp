#include "tileset.h"

Tile jsonToTile(json &t, int index) {
  return Tile(
    t.at(0).get<int>(),
    t.at(1).get<int>(),
    index
  );
}

int Grid::findSurroundings(json &t, int i, json &data) {
  
  Tile t1 = jsonToTile(t, i);

  int x = this->getX(t1.locationIndex);
  int y = this->getY(t1.locationIndex);

  int surrounding = 0;

  Tile t2;
  int index;

  if (this->isInside(x, y - 1)) {
    index = this->getIndex(x, y - 1);
    t2 = jsonToTile(data.at(index), index);

    if (t1 == t2) surrounding += Compass::NORTH;
  }

  if (this->isInside(x + 1, y - 1)) {
    index = this->getIndex(x + 1, y - 1);
    t2 = jsonToTile(data.at(index), index);
    if (t1 == t2) surrounding += Compass::NORTHEAST;
  }

  if (this->isInside(x + 1, y)) {
    index = this->getIndex(x + 1, y);
    t2 = jsonToTile(data.at(index), index);
    if (t1 == t2) surrounding += Compass::EAST;
  }

  if (this->isInside(x + 1, y + 1)) {
    index = this->getIndex(x + 1, y + 1);
    t2 = jsonToTile(data.at(index), index);
    if (t1 == t2) surrounding += Compass::SOUTHEAST;
  }

  if (this->isInside(x, y + 1)) {
    index = this->getIndex(x, y + 1);
    t2 = jsonToTile(data.at(index), index);
    if (t1 == t2) surrounding += Compass::SOUTH;
  }

  if (this->isInside(x - 1, y + 1)) {
    index = this->getIndex(x - 1, y + 1);
    t2 = jsonToTile(data.at(index), index);
    if (t1 == t2) surrounding += Compass::SOUTHWEST;
  }

  if (this->isInside(x - 1, y)) {
    index = this->getIndex(x - 1, y);
    t2 = jsonToTile(data.at(index), index);
    if (t1 == t2) surrounding += Compass::WEST;
  }

  if (this->isInside(x - 1, y - 1)) {
    index = this->getIndex(x - 1, y - 1);
    t2 = jsonToTile(data.at(index), index);
    if (t1 == t2) surrounding += Compass::NORTHWEST;
  }

  return surrounding;
}

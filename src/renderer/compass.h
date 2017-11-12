#ifndef COMPASS_H
#define COMPASS_H

#include <iostream>

using namespace std;

enum Compass {
  NORTH = 2,
  NORTHEAST = 4,
  EAST = 8,
  SOUTHEAST = 16,
  SOUTH = 32,
  SOUTHWEST = 64,
  WEST = 128,
  NORTHWEST = 256,
};

inline ostream& operator << (ostream &os, Compass const &c) {
  os << "Compass<";
  if (c & Compass::NORTH) os << "North ";
  if (c & Compass::NORTHEAST) os << "Northeast ";
  if (c & Compass::EAST) os << "East ";
  if (c & Compass::SOUTHEAST) os << "Southeast ";
  if (c & Compass::SOUTH) os << "South ";
  if (c & Compass::SOUTHWEST) os << "Southwest ";
  if (c & Compass::WEST) os << "West ";
  if (c & Compass::NORTHWEST) os << "Northwest ";
  os << ">";
  return os;
}

enum Actions {
  MAIN = 2,
  SECONDARY = 4,
  ATTACK1 = 8,
};

#endif

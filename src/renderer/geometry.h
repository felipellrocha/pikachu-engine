#ifndef GEOMETRY_H
#define GEOMETRY_H

struct point {
  int x;
  int y;

  point(int _x, int _y) : x(_x), y(_y) { };
  point() : point(0, 0) { };
};

struct dimension {
  int w;
  int h;

  dimension(int _w, int _h) : w(_w), h(_h) { };
};

struct rect {
  int x;
  int y;
  int w;
  int h;

  rect(int _x, int _y, int _w, int _h)
    : x(_x), y(_y), w(_w), h(_h) { };

  rect() : rect(0, 0, 0, 0) { };
};

#endif

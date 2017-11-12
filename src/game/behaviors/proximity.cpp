#include "proximity.h"

Status Proximity::update() {
  auto o_p = manager->getComponent<PositionComponent>(owner);
  auto o_d = manager->getComponent<DimensionComponent>(owner);

  EID player = manager->getSpecial("player");
  auto p_p = manager->getComponent<PositionComponent>(player);
  auto p_d = manager->getComponent<DimensionComponent>(player);

  int x1 = o_p->x + (o_d->w / 2);
  int y1 = o_p->y + (o_d->h / 2);

  int x2 = p_p->x + (p_d->w / 2);
  int y2 = p_p->y + (p_d->h / 2);

  int xd = x2 - x1;
  int yd = y2 - y1;

  int d = (xd * xd) + (yd * yd);

  return (d <= distance) ? Status::SUCCESS : Status::FAILURE;
};

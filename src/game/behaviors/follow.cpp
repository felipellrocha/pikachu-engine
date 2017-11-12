#include "follow.h"

Status Follower::update() {
  auto movement = manager->getComponent<MovementComponent>(owner);
  auto walk = manager->getComponent<WalkComponent>(owner);
  auto o_p = manager->getComponent<PositionComponent>(owner);

  EID player = manager->getSpecial("player");
  auto p_p = manager->getComponent<PositionComponent>(player);

  int xDiff = o_p->x - p_p->x;
  if (xDiff > 0) {
    o_p->nextX -= movement->slow.x;
    walk->direction = Compass::WEST;

    if (!(o_p->direction & Compass::WEST)) o_p->direction += Compass::WEST;
    if (o_p->direction & Compass::EAST) o_p->direction -= Compass::EAST;
  }
  else if (xDiff < 0) {
    o_p->nextX += movement->slow.x;
    walk->direction = Compass::EAST;

    if (!(o_p->direction & Compass::EAST)) o_p->direction += Compass::EAST;
    if (o_p->direction & Compass::WEST) o_p->direction -= Compass::WEST;
  }
  else {
    if (o_p->direction & Compass::EAST) o_p->direction -= Compass::EAST;
    if (o_p->direction & Compass::WEST) o_p->direction -= Compass::WEST;
  }

  int yDiff = o_p->y - p_p->y;
  if (yDiff > 0) {
    o_p->nextY -= movement->slow.y;
    walk->direction = Compass::NORTH;

    if (!(o_p->direction & Compass::NORTH)) o_p->direction += Compass::NORTH;
    if (o_p->direction & Compass::SOUTH) o_p->direction -= Compass::SOUTH;
  }
  else if (yDiff < 0) {
    o_p->nextY += movement->slow.y;
    walk->direction = Compass::SOUTH;

    if (!(o_p->direction & Compass::SOUTH)) o_p->direction += Compass::NORTH;
    if (o_p->direction & Compass::NORTH) o_p->direction -= Compass::NORTH;
  }
  else {
    if (o_p->direction & Compass::SOUTH) o_p->direction -= Compass::SOUTH;
    if (o_p->direction & Compass::NORTH) o_p->direction -= Compass::NORTH;
  }

  if (yDiff != 0 || xDiff != 0) walk->animating = true;
  else walk->animating = false;

  return Status::SUCCESS;
};

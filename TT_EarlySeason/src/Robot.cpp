#include "vex.h"
#include "Robot.h"

Robot::Robot(int x_pos, int y_pos) : x(x_pos), y(y_pos) {}

int Robot::getX() {
  return x;
}

void Robot::setX(int newX) {
  x = newX;
}
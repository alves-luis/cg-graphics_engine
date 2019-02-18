#include "Point.h"

/**
 * Class that represents a point in the system
*/

#include <sstream>

Point::Point() {
  this->x = 0;
  this->y = 0;
  this->z = 0;
}

Point::Point(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

float Point::getX() const {
  return this->x;
}

float Point::getY() const {
  return this->y;
}

float Point::getZ() const {
  return this->z;
}

void Point::setX(float x){
  this->x = x;
}

void Point::setY(float y) {
  this->y = y;
}

void Point::setZ(float z) {
  this->z = z;
}

std::string Point::toString() {
  std::ostringstream result;
  result << "X: " << this->x << " | Y: " << this->y << " | Z: " << this->z;
  return result.str();
}
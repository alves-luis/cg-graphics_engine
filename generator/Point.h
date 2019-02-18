#ifndef CG_GENERATOR_POINT_H
#define CG_GENERATOR_POINT_H

#include <string>

class Point {

private:
    float x;
    float y;
    float z;

public:
  Point();
  Point(float x, float y, float z);
  float getX() const;
  float getY() const;
  float getZ() const;
  void setX(float x);
  void setY(float y);
  void setZ(float z);
  std::string toString();
};


#endif

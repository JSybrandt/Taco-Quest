#pragma once
#include"enemy.h"

namespace Burger_ns{
  const unsigned int MAX_HEALTH = 5;
  const float SHOT_COOLDOWN = 0.5;
  const float SHOT_PROB = 0.2;
  const float SPEED = 200;
};

class Burger: public Enemy{
public:
  void spawn(Vector2f loc);
  virtual void update(float ts);
  void shoot();
protected:
  WaypointPath travelPath;
  virtual void setDefVals();
};

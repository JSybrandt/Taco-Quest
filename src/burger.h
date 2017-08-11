#pragma once
#include"enemy.h"

namespace Burger_ns{
  const unsigned int MAX_HEALTH = 5;
  const float SHOT_COOLDOWN = 0.5;
};

class Burger: public Enemy{
public:
  Burger();
  void spawn(Vector2f loc){Enemy::spawn(loc, Burger_ns::MAX_HEALTH);}
  virtual void update(float ts);
  void shoot();
};

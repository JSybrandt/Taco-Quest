#pragma once
#include"actor.h"

namespace Enemy_ns{
  const float FLASH_TIME = 0.1;
  const Color CLR_FLASH = Gc::RED;
};

class Enemy: public Actor{
public:
  Enemy();
  virtual void update(float ts);
  void spawn(Vector2f loc, unsigned int health);
  void hit();
private:
  unsigned int health, maxHealth;
  float flashCooldown;
  Color healthyColor;

};

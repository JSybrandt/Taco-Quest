#pragma once
#include"actor.h"
#ifdef DEBUG
#include<iostream>
using std::cout;
using std::endl;
#endif

namespace Enemy_ns{
  const float FLASH_COOLDOWN = 0.1;
  const Color CLR_FLASH = Gc::RED;
};

class Enemy: public Actor{
public:
  Enemy();
  virtual void update(float ts);
  void spawn(Vector2f loc, unsigned int health);
  void hit();
  virtual void shoot() = 0;
protected:
  unsigned int health, maxHealth;
  float flashTimer;
  float shootTimer;
  float shotCooldown;
  float shotProb;
  Color healthyColor;
  void setDefVals();
};

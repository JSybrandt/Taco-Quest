#pragma once
#include"actor.h"
#include"travelPath.h"

namespace Enemy_ns{
  const float FLASH_COOLDOWN = 0.1;
  const Color CLR_FLASH = Gc::RED;
};

class Enemy: public Actor{
public:
  Enemy();
  virtual void update(float ts);
  void spawn(Vector2f loc, unsigned int health, TravelPath& path);
  void hit();
  virtual void shoot() = 0;
protected:
  unsigned int health, maxHealth;
  float flashTimer;
  float shootTimer;
  float shotCooldown;
  float shotProb;
  Color healthyColor;
  virtual void setDefVals(); // called on spawn
  TravelPath* travelPath;
  float speed;

};

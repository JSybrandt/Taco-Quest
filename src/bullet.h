#pragma once
#include"actor.h"

class Bullet: public Actor{
public:
  Bullet();
  void update(float ts);
  void setVel(Vector2f vel);
  Vector2f getVel();
  void spawn(Vector2f pos, Vector2f vel);
private:
  Vector2f velocity;
};

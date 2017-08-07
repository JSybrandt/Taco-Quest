#pragma once
#include"actor.h"

class Bullet: public Actor{
public:
  Bullet();
  virtual void update(float ts);
  void setVel(Vector2f vel);
  Vector2f getVel();
  void spawn(Vector2f pos, Vector2f vel);
  void init(Game* game, const Texture& texture, Color color);
private:
  Vector2f velocity;
};

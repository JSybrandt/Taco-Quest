#pragma once
#include"actor.h"

class Enemy: public Actor{
public:
  virtual void update(float ts);
  void spawn(Vector2f loc);


};

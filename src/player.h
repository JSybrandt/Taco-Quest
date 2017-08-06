#pragma once

#include<SFML/System.hpp>
#include"actor.h"

using sf::Keyboard;

class Game;

namespace Player_ns{
  const float SPEED = 10;
  const Vector2f BULLET_SPAWN_DIST(1,0);
  const Vector2f BULLET_SPAWN_DIR(SPEED * 2,0);
  const float SHOOT_COOLDOWN = .1;
};

class Player: public Actor{
public:
  Player();
  virtual void update(float ts);
private:
  void keepOnScreen();
  float shootTimer;
};

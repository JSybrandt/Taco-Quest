#pragma once

#include<SFML/System.hpp>
#include"actor.h"

using sf::Keyboard;

class Game;

namespace Player_ns{
  const float SPEED = 10;
  const Vector2f BULLET_SPAWN_DIST(0,5);
  const Vector2f BULLET_SPAWN_DIR(0,1);
  const float SHOOT_COOLDOWN = 1;
};

class Player: public Actor{
public:
  Player();
  void update(float ts);
private:
  void keepOnScreen();
  float shootTimer;
};

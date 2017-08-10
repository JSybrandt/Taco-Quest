#pragma once

#include<SFML/System.hpp>
#include"actor.h"

using sf::Keyboard;

class Game;

namespace Player_ns{
  const float SPEED = 10;
  const unsigned int NUM_SHOOT_LEVELS = 5;
  const float SHOOT_COOLDOWNS[NUM_SHOOT_LEVELS] = {0.2, 0.15, 0.2, 0.2, 0.2};
  const float SHOOT_SPEEDS[NUM_SHOOT_LEVELS] = {10, 20, 20, 20, 20};
  const Color SHOOT_COLORS[NUM_SHOOT_LEVELS] = {
    Color(0xE8, 0xA5, 0x3C), // 0
    Color(0xD3, 0x69, 0x30), // 1
    Color(0x6E, 0x6C, 0x35), // 2
    Color(0xBD, 0x40, 0x32), // 3
    Color(0xBD, 0x40, 0x32), // 4
  };
};

class Player: public Actor{
public:
  Player();
  virtual void update(float ts);
  void levelUp();
  void levelDown();
  unsigned int getShootLevel();
private:
  void keepOnScreen();
  void shootL0();
  void shootL1();
  void shootL2();
  void shootL3();
  void shootL4();
  float shootTimer;
  unsigned int shootLevel;
};

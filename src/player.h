#pragma once

#include<SFML/System.hpp>
#include<memory>
#include"actor.h"

using sf::Keyboard;
using std::shared_ptr;
using std::make_shared;

class Game;

namespace Player_ns{
  const float SPEED = 600;
  const unsigned int NUM_SHOOT_LEVELS = 6;
  const float SHOOT_COOLDOWNS[NUM_SHOOT_LEVELS] = {0.2, 0.2, 0.2, 0.2, 0.2, 0.1};
  const float SHOOT_SPEEDS[NUM_SHOOT_LEVELS] = {
    240,
    240,
    320,
    320,
    440,
    500};
  const Color SHOOT_COLORS[NUM_SHOOT_LEVELS] = {
    Color(0xE8, 0xA5, 0x3C), // 0
    Color(0xD3, 0x69, 0x30), // 1
    Color(0x6E, 0x6C, 0x35), // 2
    Color(0xBD, 0x40, 0x32), // 3
    Color(0xBD, 0x40, 0x32), // 4
    Color(0xFF, 0xFF, 0xFF), // 5
  };
};

class Player: public Actor{
public:
  Player();
  virtual void update(float ts);
  void levelUp();
  void levelDown();
  unsigned int getShootLevel();
  void hit();
  void die();
private:
  void keepOnScreen();
  void shootL0();
  void shootL1();
  void shootL2();
  void shootL3();
  void shootL4();
  void shootL5();
  float shootTimer;
  unsigned int shootLevel;
};

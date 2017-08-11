#include"burger.h"
#include"game.h"

using namespace Burger_ns;
using namespace Gc;

Burger::Burger():Enemy(){
  this->shotCooldown = SHOT_COOLDOWN;
  this->shotProb = 0.2;
}

void Burger::update(float ts){
  if(!isActive)
    return;
  Enemy::update(ts);
  this->move(LEFT);
}

void Burger::shoot(){
  game->spawnEnemyBullet(getPos(), LEFT * 5.0f, PathData(RED));
}

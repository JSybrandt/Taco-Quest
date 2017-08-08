#include"enemy.h"

using namespace Gc;
using namespace Enemy_ns;

Enemy::Enemy():Actor(){
  flashCooldown = 0;
  healthyColor = WHITE;
};

void Enemy::update(float ts){
  flashCooldown = max(0.0f, flashCooldown - ts);
  getSprite().setColor(interpolate(healthyColor,
                                   CLR_FLASH,
                                   flashCooldown / FLASH_TIME));
}

void Enemy::spawn(Vector2f loc, unsigned int health){
  isActive = true;
  setPos(loc);
  this->health = health;
  this->maxHealth = health;
}

void Enemy::hit(){
  health--;
  flashCooldown = FLASH_TIME;
  healthyColor = interpolate(BLACK, WHITE, health / float(maxHealth));
  if(health == 0){
    die();
  }
}

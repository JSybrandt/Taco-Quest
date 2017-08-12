#include"enemy.h"

using namespace Gc;
using namespace Enemy_ns;

Enemy::Enemy():Actor(){
  setDefVals();
};

void Enemy::setDefVals(){
  flashTimer = 0;
  shootTimer = 0;
  shotCooldown = 1;
  shotProb = 1;
  healthyColor = WHITE;
  getSprite().setColor(WHITE);
  speed = 1;
  travelPath = nullptr;
}

void Enemy::update(float ts){
  if(!isActive)
    return;
  flashTimer = max(0.0f, flashTimer - ts);
  shootTimer = max(0.0f, shootTimer - ts);
  getSprite().setColor(interpolate(healthyColor,
                                   CLR_FLASH,
                                   flashTimer / FLASH_COOLDOWN));
  if(shootTimer == 0){
    if(rand01()  < shotProb)
      shoot();
    shootTimer += shotCooldown;
  }

  if(travelPath){
    move(travelPath->getNewVel(getPos(), speed, ts));
    if(travelPath->isPathingFinished())
      isActive = false;
  }
}

void Enemy::spawn(Vector2f loc, unsigned int health, TravelPath& path){
  isActive = true;
  setDefVals();
  setPos(loc);
  this->health = health;
  this->maxHealth = health;
  this->travelPath = &path;
}

void Enemy::hit(){
  health--;
  flashTimer = FLASH_COOLDOWN;
  healthyColor = interpolate(BLACK, WHITE, health / float(maxHealth));
  if(health == 0){
    die();
  }
}


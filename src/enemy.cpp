#include"enemy.h"

void Enemy::update(float ts){
  //do nothing
}

void Enemy::spawn(Vector2f loc){
  isActive = true;
  setPos(loc);
}

#include"bullet.h"
#include"game.h"

using namespace Gc;

Bullet::Bullet(){
  isActive = false;
  health = 0;
  color = WHITE;
  travelPath = nullptr;
  speed = 0;
}

void Bullet::update(float ts){
  if(isActive && travelPath){
    float x = this->getPos().x;
    isActive = x > 0 && x < game->getScreenRect().width;
    move(travelPath->getNewVel(getPos(), this->speed, ts));
  }
}

void Bullet::spawn(Vector2f pos, float speed, shared_ptr<TravelPath> path, Color color, BoltType type){
  setPos(pos);
  this->travelPath = path;
  this->isActive = true;
  this->speed = speed;
  Vector2f oldScale = this->getSprite().getScale();
  this->getSprite().scale(1/oldScale.x, 1/oldScale.y);
  health = 1;
  switch(type){
    case Circle:
      this->getSprite().scale(Vector2f(1,1)); break;
    case Wide:
      this->getSprite().scale(Vector2f(1,2)); break;
    case Big:
      this->getSprite().scale(Vector2f(5,5));
      health = 5; break;
  }
  this->getSprite().setColor(color);
}

void Bullet::init(Game* game, const Texture& texture){
  Actor::init(game, texture);
}

void Bullet::hit(){
  health--;
  if(health == 0)
    die();
}

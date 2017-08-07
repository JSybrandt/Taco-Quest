#include"bullet.h"
#include"game.h"

Bullet::Bullet(){
  isActive = false;
}

void Bullet::update(float ts){
  if(isActive){
    move(velocity);
    isActive = this->inside(game->getScreenRect());
  }
}

void Bullet::spawn(Vector2f pos, Vector2f vel){
  setPos(pos);
  setVel(vel);
  isActive = true;
}

void Bullet::setVel(Vector2f vel){
  velocity = vel;
}

Vector2f Bullet::getVel(){
  return velocity;
}

void Bullet::init(Game* game, const Texture& texture, Color color){
  Actor::init(game, texture);
  this->getSprite().setColor(color);
}


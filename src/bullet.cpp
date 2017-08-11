#include"bullet.h"
#include"game.h"

using namespace Gc;

PathData::PathData(){
  this->pathType = Straight;
  this->color = WHITE;
  this->boltType = Circle;
}
PathData::PathData(Color color, BoltType type){
  this->pathType = PathType::Straight;
  this->color = color;
  this->boltType = type;
}
PathData::PathData(Color color, float amp, float period, bool neg, BoltType type){
  this->pathType = PathType::Sin;
  this->boltType = type;
  this->amplitude = amp;
  this->period = period;
  this->sign = (neg ? -1 : 1);
  this->color = color;
}

Vector2f PathData::getVelocity(float clock, Vector2f initVel){
  switch(pathType){
    case Straight:
      return initVel;
    case Sin:
      Transform transform;
      transform.rotate(90);
      Vector2f normal = transform * initVel;
      normal *= float(cos(clock / period * 2 * PI) * amplitude * sign);
      return initVel + normal;
  }
  return initVel;
}

Bullet::Bullet(){
  isActive = false;
  health = 0;
}

void Bullet::update(float ts){
  if(isActive){
    travelClock += ts;
    move(pathData.getVelocity(travelClock, velocity));
    float x = this->getPos().x;
    isActive = x > 0 && x < game->getScreenRect().width;
  }
}

void Bullet::spawn(Vector2f pos, Vector2f vel, PathData data){
  travelClock = 0;
  setPos(pos);
  setVel(vel);
  isActive = true;
  this->pathData = data;
  Vector2f oldScale = this->getSprite().getScale();
  this->getSprite().scale(1/oldScale.x, 1/oldScale.y);
  health = 1;
  switch(data.boltType){
    case Circle:
      this->getSprite().scale(Vector2f(1,1)); break;
    case Wide:
      this->getSprite().scale(Vector2f(1,2)); break;
    case Big:
      this->getSprite().scale(Vector2f(5,5));
      health = 5; break;
  }
  this->getSprite().setColor(data.color);
}

void Bullet::setVel(Vector2f vel){
  velocity = vel;
}

Vector2f Bullet::getVel(){
  return velocity;
}

void Bullet::init(Game* game, const Texture& texture){
  Actor::init(game, texture);
}

void Bullet::hit(){
  health--;
  if(health == 0)
    die();
}

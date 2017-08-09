#include"bullet.h"
#include"game.h"

using namespace Gc;

PathData::PathData(){type = PathType::Straight;}

PathData::PathData(float amp, float period, bool neg){
  type = PathType::Sin;
  this->amplitude = amp;
  this->period = period;
  this->sign = (neg ? -1 : 1);
}

Vector2f PathData::getVelocity(float clock, Vector2f initVel){
  switch(type){
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
}

void Bullet::update(float ts){
  if(isActive){
    travelClock += ts;
    move(pathData.getVelocity(travelClock, velocity));
    isActive = this->inside(game->getScreenRect());
  }
}

void Bullet::spawn(Vector2f pos, Vector2f vel, PathData data){
  travelClock = 0;
  setPos(pos);
  setVel(vel);
  isActive = true;
  this->pathData = data;
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


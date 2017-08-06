#include"actor.h"

#include"game.h"

void Actor::init(Game* game){
  this->game = game;
}

void Actor::draw(RenderWindow & window) const{
  if(isActive){
    window.draw(this->sprite);
  }
}

void Actor::setTexture(const Texture& texture){
  sprite.setTexture(texture);
}

Sprite& Actor::getSprite(){
  return sprite;
}

bool Actor::isTouching(Actor& other){
  return this->getRect().intersects(other.getRect());
}

Rect<float> Actor::getRect() const{
  return sprite.getGlobalBounds();
}

Vector2f Actor::getPos() const{
  return sprite.getOrigin();
}

void Actor::setPos(Vector2f pos){
  sprite.setPosition(pos);
}

void Actor::move(Vector2f pos){
  sprite.move(pos);
}

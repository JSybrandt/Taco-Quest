#include"actor.h"

#include"game.h"

void Actor::init(Game* game, const Texture& texture){
  this->game = game;
  this->isInit = true;
  setTexture(texture);
}

void Actor::draw(RenderWindow & window) const{
  if(isActive && isInit){
    window.draw(this->sprite);
  }
}

void Actor::setTexture(const Texture& texture){
  sprite.setTexture(texture);
  Rect<float> texBox = sprite.getGlobalBounds();
  sprite.setOrigin(texBox.width/2, texBox.height/2);
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
  return sprite.getPosition();
}

void Actor::setPos(Vector2f pos){
  sprite.setPosition(pos);
}

void Actor::move(Vector2f pos){
  sprite.move(pos);
}

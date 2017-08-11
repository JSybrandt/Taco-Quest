#include"actor.h"

#include"game.h"

Actor::Actor(){
  game = nullptr;
  collisionType = CollisionType::Sphere;
}

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

bool Actor::checkCollision(const Actor& other){
  if(!this->isActive || !other.isActive)
    return false;
  if(this->collisionType == other.collisionType){
    if(this->collisionType == CollisionType::AABB)
      return AaBb2AaBbCollision(other);
    if(this->collisionType == CollisionType::Sphere)
      return AaBb2AaBbCollision(other);
  } else {
    if(this->collisionType == CollisionType::Sphere)
      return other.AaBb2SphereCollision(*this);
    if(this->collisionType == CollisionType::AABB)
      return this->AaBb2SphereCollision(other);
  }
  return false;
}

bool Actor::AaBb2AaBbCollision(const Actor& other) const {
  return this->getRect().intersects(other.getRect());
}
bool Actor::Sphere2SphereCollision(const Actor& other) const {
  pair<Vector2f, float> s1 = this->getSphere();
  pair<Vector2f, float> s2 = other.getSphere();
  Vector2f diff = s1.first - s2.first;
  float bothRadSqrd = pow(s1.second + s2.second, 2);
  return vecLengthSqrd(diff) < bothRadSqrd;
}

bool Actor::AaBb2SphereCollision(const Actor& other) const{
  auto oneDDist = [&] (float point, float lMin, float lMax) -> float {
    float res = 0;
    if(point < lMin){
      res += pow(lMin - point, 2);
    }
    if(point > lMax){
      res += pow(lMax - point, 2);
    }
    return res;
  };
  Rect<float> rect = this->getRect();
  pair<Vector2f, float> sphere = other.getSphere();
  float dist = 0;
  dist += oneDDist(sphere.first.x, rect.left, rect.left + rect.width);
  dist += oneDDist(sphere.first.y, rect.top, rect.top + rect.height);
  return dist < pow(sphere.second, 2);
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

void Actor::die(){
  isActive = false;
}

pair<Vector2f, float> Actor::getSphere() const{
  Rect<float> rect = getRect();
  float y = rect.top + rect.height/2;
  float x = rect.left + rect.width/2;
  float r = min(rect.height, rect.width)/2;
  return pair<Vector2f, float>(Vector2f(x, y), r);
}

bool Actor::isOnScreen(){
  const static float SCREEN_MARGIN = 50;
  Rect<float> screenRect = game->getScreenRect();
  screenRect.left -= SCREEN_MARGIN;
  screenRect.top -= SCREEN_MARGIN;
  screenRect.width += 2*SCREEN_MARGIN;
  screenRect.height += 2*SCREEN_MARGIN;
  return screenRect.contains(getPos());
}

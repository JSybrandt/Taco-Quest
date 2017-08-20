#pragma once
#include"actor.h"
#include"travelPath.h"
#include<memory>

using sf::Transform;
using sf::Color;
using std::shared_ptr;

enum BoltType{Circle, Wide, Big};

class Bullet: public Actor{
public:
  Bullet();
  virtual void update(float ts);
  void spawn(Vector2f pos,
             float speed,
             shared_ptr<TravelPath> path,
             Color color,
             BoltType type = Circle);
  void init(Game* game, const Texture& texture);
  void hit();
private:
  Vector2f velocity;
  shared_ptr<TravelPath> travelPath;
  unsigned int health;// almost always 1 but sometimes larger for Big
  Color color;
  float speed;
};

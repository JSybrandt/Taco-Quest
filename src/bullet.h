#pragma once
#include"actor.h"

using sf::Transform;
using sf::Color;

enum PathType{Straight, Sin};
enum BoltType{Circle, Wide, Big};

struct PathData{
  PathData();
  PathData(Color color, BoltType type = Circle);
  PathData(Color color, float amp, float period, bool neg = false, BoltType type = Circle);
  Vector2f getVelocity(float clock, Vector2f initVel);
  PathType pathType;
  BoltType boltType;
  float amplitude;
  float period;
  float sign;
  Color color;
};

class Bullet: public Actor{
public:
  Bullet();
  virtual void update(float ts);
  void setVel(Vector2f vel);
  Vector2f getVel();
  void spawn(Vector2f pos, Vector2f vel, PathData data);
  void init(Game* game, const Texture& texture);
  void hit();
private:
  Vector2f velocity;
  PathData pathData;
  float travelClock;
  unsigned int health;// almost always 1 but sometimes larger for Big
};

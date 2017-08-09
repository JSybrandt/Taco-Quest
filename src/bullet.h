#pragma once
#include"actor.h"

using sf::Transform;

enum PathType{Straight, Sin};
struct PathData{
  PathData();
  PathData(float amp, float freq, bool neg = false);
  Vector2f getVelocity(float clock, Vector2f initVel);
  PathType type;
  float amplitude;
  float period;
  float sign;
};

class Bullet: public Actor{
public:
  Bullet();
  virtual void update(float ts);
  void setVel(Vector2f vel);
  Vector2f getVel();
  void spawn(Vector2f pos, Vector2f vel, PathData data);
  void init(Game* game, const Texture& texture, Color color);
private:
  Vector2f velocity;
  PathData pathData;
  float travelClock;
};

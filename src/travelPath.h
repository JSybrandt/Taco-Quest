#pragma once
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<vector>

#include"constants.h"
using sf::Vector2f;
using sf::Color;
using sf::Transform;
using std::vector;

#include<iostream>
using std::cout;

class TravelPath{
public:
  TravelPath();
  // this defines the default, go right
  virtual Vector2f getNewVel(Vector2f oldPos, float speed, float ts)=0;
  bool isPathingFinished();
protected:
  bool finished;
};

class StraightPath: public TravelPath{
public:
  StraightPath(Vector2f dir);
  virtual Vector2f getNewVel(Vector2f oldPos, float speed, float ts);
protected:
  Vector2f dir;
};

class SinPath: public TravelPath{
public:
  SinPath(Vector2f dir = Gc::RIGHT,
          float amplitude=0,
          float period=0,
          bool sign=false);
  virtual Vector2f getNewVel(Vector2f oldPos, float speed, float ts);
protected:
  float amplitude, period, clock;
  Vector2f direction, normalDir;
};

class WaypointPath: public TravelPath{
public:
  WaypointPath();
  WaypointPath(Vector2f* waypoints, unsigned int length);
  WaypointPath(vector<Vector2f>& waypoints);
  virtual Vector2f getNewVel(Vector2f oldPos, float speed, float ts);
protected:
  void init(Vector2f* waypoints, unsigned int length);
  unsigned int currentWaypoint;
  Vector2f* waypoints;
  unsigned int waypointLength;
};

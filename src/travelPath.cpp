#include"travelPath.h"

using namespace Gc;

TravelPath::TravelPath(){
  finished = false;
}

bool TravelPath::isPathingFinished(){
  return finished;
}
StraightPath::StraightPath(Vector2f dir){
  this->dir = normalize(dir);
}
Vector2f StraightPath::getNewVel(Vector2f oldPos, float speed, float ts){
  return (dir * speed * ts);
}

SinPath::SinPath(Vector2f dir, float amp, float period, bool sign){
  this->direction = dir;
  this->amplitude = amp * (sign ? 1 : -1);
  this->period = period;
  this->clock = 0;
  Transform transform;
  transform.rotate(90);
  this->normalDir = transform * dir;
}

Vector2f SinPath::getNewVel(Vector2f oldPos, float speed, float ts){
  clock += ts;
  Vector2f vel = direction + (normalDir * float(cos(clock / period * 2 * PI) * amplitude));
  return normalize(vel) * speed * ts;
}

WaypointPath::WaypointPath():TravelPath(){
  init(nullptr, 0);
}

WaypointPath::WaypointPath(Vector2f* waypoints, unsigned int length):TravelPath(){
  init(waypoints, length);
}
WaypointPath::WaypointPath(vector<Vector2f>& waypoints):TravelPath(){
  init(&waypoints[0], waypoints.size());
}

void WaypointPath::init(Vector2f* waypoints, unsigned int length){
  this->currentWaypoint = 0;
  this->waypointLength = length;
  this->waypoints = waypoints;
}

Vector2f WaypointPath::getNewVel(Vector2f oldPos, float speed, float ts){
  if(!isPathingFinished()){
    Vector2f dir = waypoints[currentWaypoint] - oldPos;
    float diff = vecLength(dir);
    if(diff < EPS_PATH){
      currentWaypoint++;
      if(currentWaypoint >= waypointLength){
        finished = true;
      }
    }else{
      return normalize(dir) * speed * ts;
    }
  }
  return ZERO;
}


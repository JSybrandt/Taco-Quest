#include"burger.h"
#include"game.h"

using namespace Burger_ns;
using namespace Gc;

void Burger::setDefVals(){
  Enemy::setDefVals();
  this->shotCooldown = SHOT_COOLDOWN;
  this->shotProb = SHOT_PROB;
  this->speed = SPEED;
}

void Burger::update(float ts){
  if(!isActive)
    return;
  Enemy::update(ts);
}

void Burger::shoot(){
  game->spawnEnemyBullet(getPos(),
      5.0f,
      make_shared<StraightPath>(LEFT),
      RED);
}

void Burger::spawn(Vector2f loc){
//  Rect<float> r = game->getScreenRect();
//  static Vector2f v[] = {Vector2f(r.width, r.height),
//                  Vector2f(r.width/2, r.height),
//                  Vector2f(r.width/2, r.height/2),
//                  Vector2f(0, r.height/2)};
//  this->travelPath = WaypointPath(v, 4);

  Enemy::spawn(loc, MAX_HEALTH, make_shared<SinPath>(SinPath(LEFT, 10, 1)));
}

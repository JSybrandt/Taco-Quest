#include"player.h"
#include"game.h"

using namespace Player_ns;
using namespace Gc;

Player::Player():Actor(){
  isActive = true;
  shootTimer = 0;
  shootLevel = 0;
}

void Player::update(float ts){
  if(!isActive)
    return;

#ifdef DEBUG
  static bool buttDown = false;
  if(Keyboard::isKeyPressed(Keyboard::Key::Up)){
    if(!buttDown)
      levelUp();
    buttDown = true;
  } else if(Keyboard::isKeyPressed(Keyboard::Key::Down)){
    if(!buttDown)
      levelDown();
    buttDown = true;
  } else {
    buttDown = false;
  }
#endif

  Vector2f input(0, 0);
  const Settings settings = game->getSettings();
  if(Keyboard::isKeyPressed(settings.up)){
    input += Gc::UP;
  }
  if(Keyboard::isKeyPressed(settings.down)){
    input += Gc::DOWN;
  }
  if(Keyboard::isKeyPressed(settings.left)){
    input += Gc::LEFT;
  }
  if(Keyboard::isKeyPressed(settings.right)){
    input += Gc::RIGHT;
  }
  if (input != Vector2f(0,0)){
    Vector2f vel = normalize(input) * SPEED * ts;
    getSprite().move(vel);
  }
  keepOnScreen();

  shootTimer = max(0.0f, shootTimer - ts);
  if(shootTimer == 0 && Keyboard::isKeyPressed(settings.shoot)){
    switch(shootLevel){
      case 0: shootL0(); break;
      case 1: shootL1(); break;
      case 2: shootL2(); break;
      case 3: shootL3(); break;
      case 4: shootL4(); break;
      case 5: shootL5(); break;
      default: shootL0();
               cerr << "INVALID SHOOT LEVEL" << endl;
               break;
    }
    shootTimer = SHOOT_COOLDOWNS[shootLevel];
  }
}

void Player::keepOnScreen(){
  Rect<float> scRect = game->getScreenRect();
  Rect<float> plRect = this->getRect();
  Vector2f pos(0, 0);
  pos.x += max(0.0f, scRect.left - plRect.left);
  pos.x += min(0.0f, (scRect.left + scRect.width) - (plRect.left + plRect.width));
  pos.y += max(0.0f, scRect.top - plRect.top);
  pos.y += min(0.0f, (scRect.top + scRect.height) - (plRect.top + plRect.height));
  this->move(pos);
}

void Player::levelUp(){
  if(shootLevel < NUM_SHOOT_LEVELS-1)
    shootLevel++;
}

void Player::levelDown(){
  if (shootLevel > 0)
    shootLevel--;
}

// one in front
void Player::shootL0(){
//  static const float MAX_ANGLE=5;
//  static const int PERIOD=2;
//  static unsigned int shotClock = 0;
//  shotClock++;
//  float deg = MAX_ANGLE * sin(shotClock/float(PERIOD));
//  Transform transform;
//  transform.rotate(deg);
  game->spawnPlayerBullet(
      getPos(),
      SHOOT_SPEEDS[shootLevel],
      make_shared<StraightPath>(StraightPath(RIGHT)),
      SHOOT_COLORS[shootLevel]);
}


void Player::shootL1(){
  static bool alt = false;
  static const float DEG = 25;
  alt = !alt;
  Transform transform;
  transform.rotate(DEG * (alt?1:-1));
  game->spawnPlayerBullet(
      getPos(),
      SHOOT_SPEEDS[shootLevel],
      make_shared<StraightPath>(
        StraightPath(transform * RIGHT)),
      SHOOT_COLORS[shootLevel]);
  game->spawnPlayerBullet(
      getPos(),
      SHOOT_SPEEDS[shootLevel],
      make_shared<StraightPath>(
        StraightPath(RIGHT)),
      SHOOT_COLORS[shootLevel]);
}

void Player::shootL2(){
  static const float AMP = 2;
  static const float PERIOD = 0.8;
  game->spawnPlayerBullet(
      getPos(),
      SHOOT_SPEEDS[shootLevel],
      make_shared<StraightPath>(
        StraightPath(RIGHT)),
      SHOOT_COLORS[shootLevel],
      Wide);
  game->spawnPlayerBullet(
      getPos(),
      SHOOT_SPEEDS[shootLevel],
      make_shared<SinPath>(
        SinPath(RIGHT, AMP, PERIOD, true)),
      SHOOT_COLORS[shootLevel]);
  game->spawnPlayerBullet(
      getPos(),
      SHOOT_SPEEDS[shootLevel],
      make_shared<SinPath>(
        SinPath(RIGHT, AMP, PERIOD, false)),
      SHOOT_COLORS[shootLevel]);
}

void Player::shootL3(){
  shootL2();
  shootL1();
}

void Player::shootL4(){
  static unsigned int shotClock = 0;
  static const float AMP = 0.5;
  static const float PERIOD = 1;

  shotClock++;
  game->spawnPlayerBullet(
      getPos(),
      SHOOT_SPEEDS[shootLevel],
      make_shared<SinPath>(
        SinPath(RIGHT, AMP, PERIOD, true)),
      SHOOT_COLORS[shootLevel]);
  game->spawnPlayerBullet(
      getPos(),
      SHOOT_SPEEDS[shootLevel],
      make_shared<SinPath>(
        SinPath(RIGHT, AMP, PERIOD, false)),
      SHOOT_COLORS[shootLevel]);

  if(shotClock % 4 == 0)
    game->spawnPlayerBullet(
        getPos(),
        SHOOT_SPEEDS[shootLevel] / 2,
        make_shared<StraightPath>(
          StraightPath(RIGHT)),
        SHOOT_COLORS[shootLevel],
        Big);
}

void Player::shootL5(){
  static unsigned int shotClock = 0;
  static const float AMP = 0.2;
  static const float PERIOD = 0.7;
  shotClock++;

  game->spawnPlayerBullet(
      getPos(),
      SHOOT_SPEEDS[shootLevel],
      make_shared<SinPath>(
        SinPath(RIGHT, AMP, PERIOD, true)),
      SHOOT_COLORS[shootLevel]);
  game->spawnPlayerBullet(
      getPos(),
      SHOOT_SPEEDS[shootLevel],
      make_shared<SinPath>(
        SinPath(RIGHT, AMP, PERIOD, false)),
      SHOOT_COLORS[shootLevel]);
  if(shotClock % 3)
    game->spawnPlayerBullet(
        getPos(),
        SHOOT_SPEEDS[shootLevel],
        make_shared<StraightPath>(
          StraightPath(LEFT)),
        SHOOT_COLORS[shootLevel]);
}

unsigned int Player::getShootLevel(){
  return shootLevel;
}

void Player::hit(){die();}
void Player::die(){isActive = false;}

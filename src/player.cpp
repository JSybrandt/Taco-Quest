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
    input /= vecLength(input);
    Vector2f vel = input * SPEED;
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
  game->spawnPlayerBullet(getPos(),
                          RIGHT * SHOOT_SPEEDS[shootLevel],
                          PathData(SHOOT_COLORS[shootLevel])
                         );
}


void Player::shootL1(){
  static bool alt = false;
  Transform transform;
  transform.scale(20, 20);

  if(alt)
    game->spawnPlayerBullet(getPos() + transform * UP,
                            RIGHT * SHOOT_SPEEDS[shootLevel] + UP,
                            PathData(SHOOT_COLORS[shootLevel])
                           );
  else
    game->spawnPlayerBullet(getPos() + transform * DOWN,
                            RIGHT * SHOOT_SPEEDS[shootLevel] + DOWN,
                            PathData(SHOOT_COLORS[shootLevel])
                           );
  alt = !alt;
}

void Player::shootL2(){
  game->spawnPlayerBullet(getPos(),
                          RIGHT * SHOOT_SPEEDS[shootLevel],
                          PathData(SHOOT_COLORS[shootLevel], Wide));
}

void Player::shootL3(){
  shootL1();
  shootL2();
}

void Player::shootL4(){
  game->spawnPlayerBullet(getPos(),
                          RIGHT * SHOOT_SPEEDS[shootLevel]);
}

unsigned int Player::getShootLevel(){
  return shootLevel;
}

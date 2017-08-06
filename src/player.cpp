#include"player.h"
#include"game.h"

using namespace Player_ns;

Player::Player():Actor(){
  isActive = true;
  shootTimer = 0;
}

void Player::update(float ts){
  if(!isActive)
    return;

  //std::cout << "X:"<< getSprite().getGlobalBounds().left << endl;
  //std::cout << "Y:"<< getSprite().getGlobalBounds().top << endl;

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
    game->spawnBullet(BULLET_SPAWN_DIST + getPos(), BULLET_SPAWN_DIR);
    shootTimer = Player_ns::SHOOT_COOLDOWN;
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

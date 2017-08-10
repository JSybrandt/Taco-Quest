#pragma once
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include"settings.h"
#include"constants.h"
#include"player.h"
#include"bullet.h"
#include"enemy.h"

using namespace sf;
using std::cerr;
using std::cout;
using std::endl;

namespace Game_ns{
  const unsigned int NUM_BULLETS = 100;
  const unsigned int NUM_ENEMIES = 100;
};
class Game{
public:
  Game();
  ~Game();
  void update(Time delta);
  void collisions();
  void draw(RenderWindow& window);
  void setWindowSize(unsigned int width, unsigned int height);
  void pause();
  void resume();
  const Settings& getSettings() const;
  Rect<float> getScreenRect() const;
  void spawnPlayerBullet(Vector2f loc, Vector2f vel, PathData data=PathData());
  void spawnEnemyBullet(Vector2f loc, Vector2f vel, PathData data=PathData());

private:
  void safeLoad(Texture & t, string path);
  void safeLoad(Font & f, string path);
  bool isPaused;
  unsigned int screenWidth, screenHeight;
  Settings settings;

  Texture blockTex, tacoTex, boltTex, burgerTex, wideBoltTex;
  Player player;
  Bullet* playerBullets;
  Bullet* enemyBullets;
  Enemy* enemies;
  Font debugFont;

};

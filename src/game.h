#pragma once
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include"settings.h"
#include"constants.h"
#include"player.h"
#include"bullet.h"

using namespace sf;
using std::cerr;
using std::cout;
using std::endl;

namespace Game_ns{
  const unsigned int NUM_BULLETS = 100;
};
class Game{
public:
  Game();
  void update(Time delta);
  void draw(RenderWindow& window);
  void setWindowSize(unsigned int width, unsigned int height);
  void pause();
  void resume();
  const Settings& getSettings() const;
  Rect<float> getScreenRect() const;
  void spawnBullet(Vector2f loc, Vector2f vel);

private:
  void safeLoad(Texture & t, string path);
  bool isPaused;
  unsigned int screenWidth, screenHeight;
  Settings settings;
  Actor* getFirstUnactivated(Actor* arr, unsigned int length);
  void initActors(Actor* arr, unsigned int length, Texture& tex);

  Texture blockTex, tacoTex, boltTex;
  Player player;
  Bullet bullets[Game_ns::NUM_BULLETS];

};

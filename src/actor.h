#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<map>
#include<cmath>
#include"constants.h"
using sf::Sprite;
using sf::Texture;
using sf::Time;
using sf::RenderWindow;
using sf::Vector2f;
using sf::Rect;
using std::pair;
using sf::Color;

class Game;

enum CollisionType{AABB, Sphere};

class Actor{
public:
  Actor();
  void init(Game* game, const Texture& texture);
  void draw(RenderWindow & window) const;
  virtual void update(float ts) = 0;
  bool checkCollision(const Actor& other);
  Sprite& getSprite();
  void setTexture(const Texture& texture);
  Rect<float> getRect() const;
  Vector2f getPos() const;
  void setPos(Vector2f pos);
  void move(Vector2f pos);
  template <class T>
  bool inside(Rect<T> r){
    return r.contains(sprite.getPosition());
  };
  void die();
  bool isActive;
  bool isInit;
  CollisionType collisionType;
  // gets inscribed sphere
  pair<Vector2f, float> getSphere() const; // center and radius
private:
  Sprite sprite;
  bool AaBb2AaBbCollision(const Actor& other) const;
  bool Sphere2SphereCollision(const Actor& other) const;
  bool AaBb2SphereCollision(const Actor& other) const;
protected:
  Game* game;
};

#pragma once

#include<SFML/Graphics.hpp>
using sf::Sprite;
using sf::Texture;
using sf::Time;
using sf::RenderWindow;
using sf::Vector2f;
using sf::Rect;

class Game;

class Actor{
public:
  Actor(){game=nullptr;}
  void init(Game* game);
  void draw(RenderWindow & window) const;
  virtual void update(float ts) = 0;
  Sprite& getSprite();
  void setTexture(const Texture& texture);
  bool isTouching(Actor& other);
  Rect<float> getRect() const;
  Vector2f getPos() const;
  void setPos(Vector2f pos);
  void move(Vector2f pos);
  template <class T>
  bool inside(Rect<T> r){
    return r.contains(sprite.getOrigin());
  };
  bool isActive;
private:
  Sprite sprite;
protected:
  Game* game;
};

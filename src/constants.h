#pragma once
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<cmath>
using sf::Vector2;
using sf::Color;
namespace Gc {
 extern const int SCREEN_WIDTH;
 extern const int SCREEN_HEIGHT;
 extern const char* TITLE;
 extern const char* SETTINGS_FILE;
 extern const char* IMG_BLOCK;
 extern const char* IMG_BOLT;
 extern const char* IMG_TACO;
 extern const char* IMG_BURGER;
 extern const Vector2<float> UP;
 extern const Vector2<float> DOWN;
 extern const Vector2<float> LEFT;
 extern const Vector2<float> RIGHT;
 extern const Color CLR_PLAYER_BULLET;
 extern const Color CLR_ENEMY_BULLET;
}

template<class T>
float vecLengthSqrd(Vector2<T> a){
  return a.x * a.x + a.y*a.y;
}
template<class T>
float vecLength(Vector2<T> a){
  return sqrt(vecLengthSqrd(a));
}

template<class T>
T max(T a, T b){
  if(a > b)
    return a;
  else return b;
}

template<class T>
T min(T a, T b){
  if(a < b)
    return a;
  else return b;
}

#pragma once
#include<SFML/Window.hpp>
#include<fstream>
#include<iostream>
#include<string>
#include<map>
using sf::Keyboard;
using std::string;
using std::fstream;
using std::ios;
using std::endl;
using std::map;
using std::cerr;

namespace SK{
  const string UP    =  "UP_KEY";
  const string DOWN  =  "DOWN_KEY";
  const string LEFT  =  "LEFT_KEY";
  const string RIGHT =  "RIGHT_KEY";
  const string SHOOT =  "SHOOT_KEY";
};

struct Settings{
  Settings(string path);
  Keyboard::Key up;
  Keyboard::Key down;
  Keyboard::Key left;
  Keyboard::Key right;
  Keyboard::Key shoot;
private:
  void writeDefaultSettings(string path);
  bool fileExists(string path);
  Keyboard::Key str2key(string str);
};

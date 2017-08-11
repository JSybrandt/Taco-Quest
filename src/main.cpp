#include<iostream>
#include<SFML/Window.hpp>

#include"game.h"
#include"constants.h"
#include"settings.h"

using namespace std;
using namespace sf;


int main(){
  RenderWindow window(VideoMode(Gc::SCREEN_WIDTH,
                                Gc::SCREEN_HEIGHT),
                      Gc::TITLE,
                      Style::Default | Style::Fullscreen);
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);

  Clock clock;
  Game game;
  Settings settings(Gc::SETTINGS_FILE);
  // for each frame
  while(window.isOpen()){

    Time delta = clock.restart();

    game.update(delta);

    game.collisions();

    //draw
    window.clear(Color::Black);
    game.draw(window);
    window.display();


    // handle events within a frame
    Event e;
    while(window.pollEvent(e)){
      if(e.type == Event::Closed){
        window.close();
      }
      if(e.type == Event::Resized){
        game.setWindowSize(e.size.width, e.size.height);
      }
      if(e.type == Event::LostFocus){
        game.pause();
      }
      if(e.type == Event::GainedFocus){
        game.resume();
      }
      if(e.type == Event::TextEntered){
        // do nothing
      }
      // note, key state will just be polled from sf::Keyboard
      if(e.type == Event::KeyReleased){
        if(e.key.code == Keyboard::Escape){
          window.close();
        }
      }
    }
  }
  return 0;
}

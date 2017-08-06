#include"game.h"

using namespace Game_ns;

Game::Game():settings(Gc::SETTINGS_FILE){
  isPaused = false;
  safeLoad(blockTex, Gc::IMG_BLOCK);
  safeLoad(boltTex, Gc::IMG_BOLT);
  safeLoad(tacoTex, Gc::IMG_TACO);
  player.setTexture(tacoTex);
  player.init(this);
  initActors(bullets, NUM_BULLETS, boltTex);
  cout << "FINISHED INIT" << endl;
}

void Game::update(Time delta){
  if(isPaused)
    return;

  float ts = delta.asSeconds();
  player.update(ts);
  for(unsigned int i = 0; i < NUM_BULLETS; ++i)
    bullets[i].update(ts);

  cout << "UPDATE" << endl;
}

void Game::spawnBullet(Vector2f loc, Vector2f vel){
  Bullet* newBul = (Bullet*) getFirstUnactivated(bullets, NUM_BULLETS);
  if(newBul){
    newBul->spawn(loc, vel);
  }
}

void Game::draw(RenderWindow& window){
  player.draw(window);
  for(unsigned int i = 0; i < NUM_BULLETS; ++i)
    bullets[i].draw(window);
}

void Game::setWindowSize(unsigned int w, unsigned int h){
  this->screenWidth = w;
  this->screenHeight = h;
}

void Game::pause(){
  this->isPaused = true;
}

void Game::resume(){
  this->isPaused = false;
}

const Settings& Game::getSettings() const{
  return settings;
}

void Game::safeLoad(Texture & t, string path){
  if(! t.loadFromFile(path)){
    cerr << "Failed to load texture:" << path << endl;
    exit(1);
  }
}

Rect<float> Game::getScreenRect() const{
  return Rect<float>(0, 0, screenWidth, screenHeight);
}

Actor* Game::getFirstUnactivated(Actor* arr, unsigned int length){
  for(unsigned int i = 0; i < length; ++i){
    if(!arr[i].isActive)
      return &arr[i];
  }
  cerr << "Failed to find an unactivated item." << endl;
  return nullptr;
}

void Game::initActors(Actor* arr, unsigned int length, Texture& tex){
  for(unsigned int i=0; i < length; ++i){
    arr[i].setTexture(tex);
    arr[i].init(this);
  }
}

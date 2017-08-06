#include"game.h"

using namespace Game_ns;

Game::Game():settings(Gc::SETTINGS_FILE){
  isPaused = false;
  bullets = new Bullet[NUM_BULLETS];
  safeLoad(blockTex, Gc::IMG_BLOCK);
  safeLoad(boltTex, Gc::IMG_BOLT);
  safeLoad(tacoTex, Gc::IMG_TACO);

  player.init(this, tacoTex);
  for(unsigned int i=0; i<NUM_BULLETS; ++i)
    bullets[i].init(this, boltTex);
}

Game::~Game(){
  delete [] bullets;
}

void Game::update(Time delta){
  if(isPaused)
    return;
  float ts = delta.asSeconds();
  player.update(ts);
  for(unsigned int i = 0; i < NUM_BULLETS; ++i){
    bullets[i].update(ts);
  }
}

void Game::spawnBullet(Vector2f loc, Vector2f vel){
  for(unsigned int i=0; i<NUM_BULLETS; ++i){
    if(!bullets[i].isActive){
      bullets[i].spawn(loc, vel);
      break;
    }
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

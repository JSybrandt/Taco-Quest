#include"game.h"

#ifdef DEBUG
#include<sstream>
using std::stringstream;
#endif

using namespace Game_ns;

Game::Game():settings(Gc::SETTINGS_FILE){
  isPaused = false;
  // Data:
  playerBullets = new Bullet[NUM_BULLETS];
  enemyBullets = new Bullet[NUM_BULLETS];
  enemies = new Enemy[NUM_ENEMIES];
  // Tex:
  safeLoad(blockTex, Gc::IMG_BLOCK);
  safeLoad(boltTex, Gc::IMG_BOLT);
  boltTex.setSmooth(true);
  safeLoad(wideBoltTex, Gc::IMG_WIDE_BOLT);
  wideBoltTex.setSmooth(true);
  safeLoad(tacoTex, Gc::IMG_TACO);
  tacoTex.setSmooth(true);
  safeLoad(burgerTex, Gc::IMG_BURGER);
  burgerTex.setSmooth(true);
  // Init:
  player.init(this, tacoTex);
  for(unsigned int i=0; i<NUM_BULLETS; ++i){
    playerBullets[i].init(this, boltTex);
    enemyBullets[i].init(this, boltTex);
  }
  for(unsigned int i=0; i<NUM_ENEMIES; ++i){
    enemies[i].init(this, burgerTex);
  }

  //spawn
  for(unsigned int i=0; i<10; ++i){
    enemies[i].spawn(Vector2f(50*i+200, 50*i+100), i+1);
  }

  // font
  safeLoad(debugFont, Gc::FONT_ARIAL);
}

Game::~Game(){
  delete [] playerBullets;
  delete [] enemyBullets;
  delete [] enemies;
}

void Game::update(Time delta){
  if(isPaused)
    return;
  float ts = delta.asSeconds();
  player.update(ts);
  for(unsigned int i = 0; i < NUM_BULLETS; ++i){
    playerBullets[i].update(ts);
    enemyBullets[i].update(ts);
  }
  for(unsigned int i = 0; i < NUM_ENEMIES; ++i){
    enemies[i].update(ts);
  }
}

void Game::collisions(){
  for(unsigned int i=0; i<NUM_BULLETS; ++i){
    for(unsigned int j=0; j<NUM_ENEMIES; ++j){
      if(playerBullets[i].checkCollision(enemies[j])){
        playerBullets[i].hit();
        enemies[j].hit();
      }
    }
  }
}

void Game::spawnPlayerBullet(Vector2f loc, Vector2f vel, PathData data){
  for(unsigned int i=0; i<NUM_BULLETS; ++i){
    if(!playerBullets[i].isActive){
      playerBullets[i].spawn(loc, vel, data);
      break;
    }
  }
}

void Game::spawnEnemyBullet(Vector2f loc, Vector2f vel, PathData data){
  for(unsigned int i=0; i<NUM_BULLETS; ++i){
    if(!enemyBullets[i].isActive){
      enemyBullets[i].spawn(loc, vel, data);
      break;
    }
  }
}

void Game::draw(RenderWindow& window){
  for(unsigned int i = 0; i < NUM_BULLETS; ++i){
    playerBullets[i].draw(window);
    enemyBullets[i].draw(window);
  }
  for(unsigned int i = 0; i < NUM_ENEMIES; ++i){
    enemies[i].draw(window);
  }
  player.draw(window);

#ifdef DEBUG
  Text debugText;
  stringstream s;
  s << "Shoot Level: " << player.getShootLevel() << endl;
  debugText.setFont(debugFont);
  debugText.setString(s.str());
  debugText.setCharacterSize(24);
  window.draw(debugText);
#endif
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
void Game::safeLoad(Font & f, string path){
  if(! f.loadFromFile(path)){
    cerr << "Failed to load font:" << path << endl;
    exit(1);
  }
}

Rect<float> Game::getScreenRect() const{
  return Rect<float>(0, 0, screenWidth, screenHeight);
}

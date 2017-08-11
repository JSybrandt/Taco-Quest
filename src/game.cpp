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
  burgers = new Burger[NUM_ENEMIES];
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
    burgers[i].init(this, burgerTex);
  }

  // font
  safeLoad(debugFont, Gc::FONT_ARIAL);
}

Game::~Game(){
  delete [] playerBullets;
  delete [] enemyBullets;
  delete [] burgers;
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
    burgers[i].update(ts);
  }

  static float spawnCooldown = 0;
  spawnCooldown = max(0.0f, spawnCooldown - ts);
  if(spawnCooldown == 0){
    if(rand01() < 0.25){
      spawnBurger(Vector2f(screenWidth * (0.5 + rand01()/2),
                           screenHeight * rand01()));
    }
    spawnCooldown = 0.5;
  }
}

void Game::collisions(){
  for(unsigned int i=0; i<NUM_BULLETS; ++i){
    for(unsigned int j=0; j<NUM_ENEMIES; ++j){
      if(playerBullets[i].checkCollision(burgers[j])){
        playerBullets[i].hit();
        burgers[j].hit();
      }
    }
  }
}

void Game::spawnBurger(Vector2f loc){
  for(unsigned int i=0; i<NUM_ENEMIES; ++i){
    if(!burgers[i].isActive){
      burgers[i].spawn(loc);
      break;
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
  for(unsigned int i = 0; i < NUM_ENEMIES; ++i){
    burgers[i].draw(window);
  }
  for(unsigned int i = 0; i < NUM_BULLETS; ++i){
    playerBullets[i].draw(window);
    enemyBullets[i].draw(window);
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

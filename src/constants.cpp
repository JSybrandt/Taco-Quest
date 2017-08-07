#include"constants.h"
namespace Gc {
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  const char* TITLE = "Taco Quest";
  const char* SETTINGS_FILE = "./settings.txt";
  const char* IMG_BLOCK = "./res/block.png";
  const char* IMG_BOLT = "./res/bolt.png";
  const char* IMG_TACO = "./res/taco.png";
  const char* IMG_BURGER = "./res/burger.png";
  const Vector2<float> UP(0, -1);
  const Vector2<float> DOWN(0, 1);
  const Vector2<float> LEFT(-1, 0);
  const Vector2<float> RIGHT(1, 0);
  const Color CLR_PLAYER_BULLET(0, 0, 255);
  const Color CLR_ENEMY_BULLET(255, 0, 0);
}

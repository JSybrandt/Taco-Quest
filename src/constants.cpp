#include"constants.h"
namespace Gc {
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  const char* TITLE = "Taco Quest";
  const char* SETTINGS_FILE = "./settings.txt";
  const char* IMG_BLOCK = "./res/block.png";
  const char* IMG_BOLT = "./res/bolt.png";
  const char* IMG_WIDE_BOLT = "./res/wideBolt.png";
  const char* IMG_TACO = "./res/taco.png";
  const char* IMG_BURGER = "./res/burger.png";
  const char* FONT_ARIAL = "./res/arial.ttf";
  const Vector2<float> UP(0, -1);
  const Vector2<float> DOWN(0, 1);
  const Vector2<float> LEFT(-1, 0);
  const Vector2<float> RIGHT(1, 0);
  const Color CLR_PLAYER_BULLET(0, 0, 255);
  const Color CLR_ENEMY_BULLET(255, 0, 0);
  const Color BLACK = Color(0, 0, 0);
  const Color WHITE = Color(255, 255, 255);
  const Color RED = Color(255, 0, 0);
  const Color GREEN = Color(0, 255, 0);
  const Color BLUE = Color(0, 0, 255);
  const float PI = 3.14159265359;
}

template<>
Color interpolate<Color>(Color colorA, Color colorB, float scale){
  unsigned short r = colorA.r * (1 - scale) + colorB.r * scale;
  unsigned short g = colorA.g * (1 - scale) + colorB.g * scale;
  unsigned short b = colorA.b * (1 - scale) + colorB.b * scale;
  return Color(r, g, b);
}

float rand01(){
  return (rand() % 1000) / 1000.0f;
}

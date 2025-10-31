#ifndef in_h
#define in_h

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)
  
enum Direction {
  Vertical,
  Horizontal
};

#define BACKGROUND BLACK

#include "../external/raylib-5.5/raylib.h"
#include "../external/raylib-5.5/raymath.h"

#endif

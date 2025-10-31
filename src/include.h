#ifndef in_h
#define in_h

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

#include "../external/raylib-5.5/raylib.h"
#include "../external/raylib-5.5/raymath.h"

#include "../external/tomlplusplus/toml.hpp"

#define BACKGROUND (Color){17, 17, 27, 255}
#define TEXT (Color){247, 236, 225, 255}
#define SUBTEXT (Color){202, 196, 206, 255}
#define HIGHLIGHT1 (Color){141, 134, 201, 255}
#define HIGHLIGHT2 (Color){114, 90, 193, 255}

#define TRANSPERENT (Color){0, 0, 0, 0}

enum Direction {
  Vertical,
  Horizontal
};

#endif

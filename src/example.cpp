#include "example.hpp"

Example::Example() : Entity2D("Example", (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f}) {}

Example::~Example() {}

void Example::process(float delta) {
  position.y += 100 * delta;
}

void Example::render() {
  ClearBackground(BLACK);
  DrawCircleV(position, 50, WHITE);
}

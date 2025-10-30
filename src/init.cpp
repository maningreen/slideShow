#include "engine/entity.hpp"
#include "widget.hpp"

void init(Entity* root) {
  Rect* x = new Rect(100, 100, 100, 100, WHITE);
  Box* box = new Box(Box::Vertical, {x});
  root->addChild(box);
}

void preRendering(Entity* root) {
  ClearBackground(BLACK);
}

void postRendering(Entity* root) {
  DrawFPS(0, 0);
}

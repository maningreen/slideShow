#include "engine/entity.hpp"
#include "widget.hpp"

void init(Entity* root) {
  Rect* x = new Rect(100, 100, 100, 100, WHITE);
  Rect* y = new Rect(100, 100, 100, 100, GREEN);
  CircleSection* z = new CircleSection((Vector2){100, 100}, 50, PI, PI / 2, GREEN);
  Circle* w = new Circle((Vector2){100, 100}, 50, BLUE);
  Circle* f = new Circle((Vector2){100, 100}, 50, BLUE);
  Box* box = hBox({vBox({x, z, y, w}), f});
  root->addChild(box);
}

void preRendering(Entity* root) {
  ClearBackground(BLACK);
}

void postRendering(Entity* root) {
  DrawFPS(0, 0);
}

#include "animatedWidgets.hpp"
#include "engine/entity.hpp"
#include "include.h"
#include "widget.hpp"

void init(Entity* root) {
  Text::loadFonts();

  AnimatedCircle* x = new AnimatedCircle(Circle({.1, .1}, 100, HIGHLIGHT1), AnimatedWidget::InOut);
  AnimatedCircle* y = new AnimatedCircle(Circle({.1, .1}, 100, HIGHLIGHT2), AnimatedWidget::InOut);
  AnimatedText* z = new AnimatedText(Text("coolio", body, {0, 0}, {10, 10}), AnimatedWidget::InOut);

  Box* box = hBox({x, y, z});
  box->position = {.1, .1};

  root->addChild(box);
}

void preRendering(Entity* root) {
  ClearBackground(BACKGROUND);
}

void postRendering(Entity* root) {
  DrawFPS(0, 0);
}

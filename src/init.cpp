#include "animatedWidgets.hpp"
#include "engine/entity.hpp"
#include "include.h"
#include "slide.hpp"
#include "toml.hpp"
#include "widget.hpp"

void init(Entity* root) {
  Text::loadFonts();

  toml::table config = toml::parse_file("test.toml");

  SlideShow* show = toml::parseSlideShow(config);

  root->addChild(show);
}

void preRendering(Entity* root) {
  ClearBackground(BACKGROUND);
}

void postRendering(Entity* root) {
  DrawFPS(0, 0);
}

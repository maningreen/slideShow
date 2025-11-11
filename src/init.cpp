#include "engine/entity.hpp"
#include "toml.hpp"
#include "widget.hpp"

void init(Entity* root) {
  Text::loadFonts();
  root->addChild(toml::parseSlideShow(toml::parse_file("resources/slideshow.toml")));
}

void preRendering(Entity* root) {
}

void postRendering(Entity* root) {
  DrawCircle(0, 0, 100, WHITE);
}

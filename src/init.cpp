#include "engine/entity.hpp"
#include "slide.hpp"
#include "toml.hpp"
#include "widget.hpp"

void init(Entity* root) {
  Text::loadFonts();
  SlideShow* x = new SlideShow(*toml::parse_file("resources/slideshow.toml").as_table());
  root->addChild(x);
}

void preRendering(Entity* root) {
}

void postRendering(Entity* root) {}

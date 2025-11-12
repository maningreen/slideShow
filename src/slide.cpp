#include "slide.hpp"
#include "engine/entity.hpp"
#include "include.h"
#include "widget.hpp"
#include "toml.hpp"
#include <vector>

Slide::~Slide() {
  for(Widget** x = widgets.data(); x < widgets.data() + widgets.size(); x++)
    (*x)->kill();
  widgets = {};
}

void Slide::process(float delta) {
  for(Widget** x = widgets.data(); x < widgets.data() + widgets.size(); x++) {
    (*x)->step(delta);
    (*x)->globalPos = (*x)->position;
  }
}

void Slide::render() {
  for(Widget** x = widgets.data(); x < widgets.data() + widgets.size(); x++)
    (*x)->render();
}

SlideShow::SlideShow(toml::table s) : Entity("SlideShow") {
  background = hexToCol(s["background"].value_or("#000000"));
  currentSlide = 0;
  s["slides"].as_array()->for_each([this](toml::table x){
    slides.push_back(x);
  });
  loadSlide();
}

SlideShow::SlideShow() : Entity("SlideShow") {
  background = BLACK;
  loadSlide();
}

SlideShow::~SlideShow() {
  delete slide;
}

void SlideShow::loadSlide() {
  toml::table x = *slides[currentSlide].as_table();
  slide = toml::parseSlide(x);
}

void SlideShow::nextSlide() {
  currentSlide = Clamp(currentSlide + 1, 0, slides.size() - 1);
  delete slide;
  loadSlide();
}

void SlideShow::previousSlide() {
  currentSlide = Clamp(currentSlide - 1, 0, slides.size() - 1);
  delete slide;
  loadSlide();
}

void SlideShow::process(float delta) {
  if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_RIGHT))
    nextSlide();
  if(IsKeyPressed(KEY_BACK) || IsKeyPressed(KEY_BACKSPACE))
    previousSlide();
  slide->process(delta);
}

void SlideShow::render() {
  slide->render();
  ClearBackground(background);
}

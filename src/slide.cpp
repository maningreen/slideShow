#include "slide.hpp"
#include "engine/entity.hpp"
#include <algorithm>
#include <vector>

Slide::~Slide() {
  for(Widget** x = widgets.data(); x < widgets.data() + widgets.size(); x++)
    (*x)->kill();
  widgets = {};
}

void Slide::process(float delta) {
  for(Widget** x = widgets.data(); x < widgets.data() + widgets.size(); x++)
    (*x)->process(delta);
}

void Slide::render() {
  for(Widget** x = widgets.data(); x < widgets.data() + widgets.size(); x++)
    (*x)->render();
}

SlideShow::SlideShow(std::vector<Slide> s) : Entity("SlideShow") {
  currentSlide = 0;
  for(Slide* x = s.data(); x < s.data() + s.size(); x++)
    addSlide(*x);
}

SlideShow::SlideShow(std::vector<Slide*> s) : Entity("SlideShow"), slides(s) {
  currentSlide = 0;
  for(Slide** x = s.data(); x < s.data() + s.size(); x++)
    addChild(*x);
}

SlideShow::SlideShow() : Entity("SlideShow") {}

void SlideShow::addSlide(Slide s) {
  Slide* n = new Slide(s);
  slides.push_back(n);
  addChild(n);
}

void SlideShow::addSlide(Slide* s) {
  slides.push_back(s);
  addChild(s);
}

SlideShow::~SlideShow() {}

void SlideShow::nextSlide() {
  currentSlide = Clamp(currentSlide + 1, 0, slides.size() - 1);
}

void SlideShow::previousSlide() {
  currentSlide = Clamp(currentSlide - 1, 0, slides.size() - 1);
}

void SlideShow::process(float delta) {
  if(IsKeyPressed(KEY_SPACE))
    nextSlide();
  else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    nextSlide();
  else if(KEY_BACK)
    previousSlide();
}

void SlideShow::render() {
  // :)
  Slide* c = slides[currentSlide];
  c->render();
}

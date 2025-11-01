#ifndef slide_h
#define slide_h

#include "engine/entity.hpp"
#include "widget.hpp"
#include <vector>

struct Slide : public Entity {
  std::vector<Widget*> widgets;

  void process(float delta) override;
  void render() override;

  Slide() : Entity("Slide") {}
  Slide(std::vector<Widget*> widgets) : widgets(widgets), Entity("Slide") {}

  ~Slide();
};

struct SlideShow : Entity {
  std::vector<Slide*> slides;

  unsigned currentSlide;

  void process(float delta) override;
  void render() override;

  void addSlide(Slide*);
  void addSlide(Slide);

  void nextSlide();
  void previousSlide();

  SlideShow(std::vector<Slide> slides);
  SlideShow(std::vector<Slide*> slides);
  SlideShow();
  ~SlideShow();
};

#endif

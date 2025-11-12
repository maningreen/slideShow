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
private:
  // WARNING: THIS METHOD DOES NOT DEINITIALIZE MEMORY
  void loadSlide();
public:
  std::vector<toml::table> slides;
  Slide* slide;

  unsigned currentSlide;

  Color background;

  void process(float delta) override;
  void render() override;

  void nextSlide();
  void previousSlide();

  SlideShow(toml::table slides);
  SlideShow();
  ~SlideShow();
};

#endif

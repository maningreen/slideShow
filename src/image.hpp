#ifndef image_h
#define image_h

#include "include.h"
#include "widget.hpp"
#include "animatedWidgets.hpp"

struct ImageWidget : Widget {
  Texture source;
  void render() override;

  Rectangle crop;
  float scale;


  ImageWidget(Image source, Vector2 p);
  ImageWidget(std::string source, Vector2 p);
  ImageWidget(char* source, Vector2 p);
  ~ImageWidget();
};

struct AnimatedImageWidget : ImageWidget {
  AnimatedWidget animation;
  float progress;
  Direction dir;

  void step(float delta) override;
  void render() override;

  AnimatedImageWidget(ImageWidget base, AnimatedWidget::easeType);
  AnimatedImageWidget(ImageWidget base, AnimatedWidget::easeType, Direction d);
  ~AnimatedImageWidget();
};

#endif

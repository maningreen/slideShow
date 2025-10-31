#ifndef animatedWidgets_h
#define animatedWidgets_h

#include "include.h"
#include "widget.hpp"
struct AnimatedWidget {
  float easeInOut(float progress);
  float easeIn(float progress);
  float easeOut(float progress);
  float ease(float progress);

  enum easeType {
    In,
    Out,
    InOut
  };

  easeType type;
  AnimatedWidget() {}
  AnimatedWidget(easeType x) : type(x) {}
  ~AnimatedWidget() {}
};

struct AnimatedRect : Rect {
  void step(float delta) override;
  void render() override;

  float progress;
  Direction dir;
  AnimatedWidget animation;
  AnimatedRect(Rect x, AnimatedWidget::easeType, Direction);
};

struct AnimatedSpacer : AnimatedRect {
  AnimatedSpacer(Spacer, AnimatedWidget::easeType, Direction);
  AnimatedSpacer(Rect, AnimatedWidget::easeType, Direction);
};

struct AnimatedCircle : Circle {
  void step(float delta) override;
  void render() override;

  float progress;
  AnimatedWidget animation;

  AnimatedCircle(Circle x, AnimatedWidget::easeType);
};

struct AnimatedCircleSection : CircleSection {
  void step(float delta) override;
  void render() override;

  float progress;
  AnimatedWidget animation;

  AnimatedCircleSection(CircleSection x, AnimatedWidget::easeType);
};

struct AnimatedCircleSectionLines : CircleSectionLines {
  void step(float delta) override;
  void render() override;

  float progress;
  AnimatedWidget animation;

  AnimatedCircleSectionLines(CircleSectionLines x, AnimatedWidget::easeType);
};

struct AnimatedText : Text {
  void step(float delta) override;
  void render() override;

  float progress;
  AnimatedWidget animation;

  AnimatedText(Text x, AnimatedWidget::easeType);
};

#endif

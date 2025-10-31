#include "animatedWidgets.hpp"
#include "include.h"
#include <cmath>

float AnimatedWidget::easeIn(float x) {
  return x * x * x;
}

float AnimatedWidget::easeOut(float x) {
  return 1 - pow(1 - x, 3);
}

float AnimatedWidget::easeInOut(float x) {
  return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2;
}

float AnimatedWidget::ease(float x) {
  switch(type) {
  case In:
    return easeIn(x);
  case Out:
    return easeOut(x);
  case InOut:
    return easeInOut(x);
  default:
    return easeInOut(x);
  }
}

AnimatedRect::AnimatedRect(Rect x, AnimatedWidget::easeType t, Direction z) : Rect(x) {
  animation = AnimatedWidget(t);
  dir = z;
  progress = 0;
}

void AnimatedRect::step(float delta) {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->process(delta);
  else
    progress += delta;
}

void AnimatedRect::render() {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->render();
  float scaleX = dir == Horizontal ? animation.ease(progress) : 1;
  float scaleY = dir == Vertical ? animation.ease(progress) : 1;
  DrawRectangle(globalPos.x, globalPos.y, dimensions.x * scaleX, dimensions.y * scaleY, colour);
}

AnimatedCircle::AnimatedCircle(Circle x, AnimatedWidget::easeType t) : Circle(x) {
  animation = AnimatedWidget(t);
  progress = 0;
}

void AnimatedCircle::step(float delta) {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->process(delta);
  else
    progress += delta;
}

void AnimatedCircle::render() {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->render();
  DrawCircleV(position, radius * animation.ease(progress), colour);
}

AnimatedCircleSection::AnimatedCircleSection(CircleSection x, AnimatedWidget::easeType t) : CircleSection(x) {
  animation = AnimatedWidget(t);
  progress = 0;
}

void AnimatedCircleSection::step(float delta) {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->process(delta);
  else
    progress += delta;
}

void AnimatedCircleSection::render() {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->render();
  float scalar = animation.ease(progress);
  DrawCircleSector(position + (Vector2){radius, radius}, radius, RAD2DEG * (centerAngle - offset * scalar), RAD2DEG * (centerAngle + offset * scalar), 12, colour);
}

AnimatedCircleSectionLines::AnimatedCircleSectionLines(CircleSectionLines x, AnimatedWidget::easeType t) : CircleSectionLines(x) {
  animation = AnimatedWidget(t);
  progress = 0;
}

void AnimatedCircleSectionLines::step(float delta) {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->process(delta);
  else
    progress += delta;
}

void AnimatedCircleSectionLines::render() {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->render();
  float scalar = animation.ease(progress);
  DrawCircleSector(position, radius, RAD2DEG * (centerAngle - offset * scalar), RAD2DEG * (centerAngle + offset * scalar), 12, colour);
  DrawCircleSector(position, radius - thickness, RAD2DEG * (centerAngle - offset * scalar), RAD2DEG * (centerAngle + offset * scalar), 12, BACKGROUND);
}

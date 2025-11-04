#include "animatedWidgets.hpp"
#include "include.h"
#include "widget.hpp"
#include <cmath>
#include <cstring>

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
  speed = 1;
}

void AnimatedRect::step(float delta) {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++) {
      entities[i]->globalPos = entities[i]->position + globalPos;
      entities[i]->step(delta);
    }
  else
    progress += delta * speed;
}

void AnimatedRect::render() {
  float offsetX = dir == Left ? dimensions.x * (1 - animation.ease(progress)) : 1;
  float offsetY = dir == Up ? dimensions.y * (1 - animation.ease(progress)) : 1;
  float scaleX = dir == Left || dir == Right ? animation.ease(progress) : 1;
  float scaleY = dir == Down || dir == Up ? animation.ease(progress) : 1;
  DrawRectangle(globalPos.x + offsetX, globalPos.y + offsetY, dimensions.x * scaleX, dimensions.y * scaleY, colour);
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->render();
}

AnimatedSpacer::AnimatedSpacer(Spacer x, AnimatedWidget::easeType t, Direction d) : 
  AnimatedRect(Rect(x.position, x.dimensions, TRANSPARENT), t, d), speed(1) {}

AnimatedSpacer::AnimatedSpacer(Rect x, AnimatedWidget::easeType t, Direction d) : 
  AnimatedRect(Rect(x.position, x.dimensions, TRANSPARENT), t, d), speed(1) {}

void AnimatedSpacer::step(float delta) {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++) {
      entities[i]->globalPos = entities[i]->position + globalPos;
      entities[i]->step(delta);
    }
  else
    progress += delta * speed;
}

void AnimatedSpacer::render() {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->render();
}

AnimatedCircle::AnimatedCircle(Circle x, AnimatedWidget::easeType t) : Circle(x) {
  animation = AnimatedWidget(t);
  dimensions = {
    radius * 2,
    radius * 2
  };
  speed = 1;
  progress = 0;
}

void AnimatedCircle::step(float delta) {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++) {
      entities[i]->globalPos = entities[i]->position + globalPos;
      entities[i]->step(delta);
    }
  else
    progress += delta * speed;
}

void AnimatedCircle::render() {
  DrawCircleV(globalPos + (Vector2){radius, radius}, radius * animation.ease(progress), colour);
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->render();
}

AnimatedCircleSection::AnimatedCircleSection(CircleSection x, AnimatedWidget::easeType t) : CircleSection(x) {
  animation = AnimatedWidget(t);
  progress = 0;
  speed = 1;
}

void AnimatedCircleSection::step(float delta) {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++) {
      entities[i]->globalPos = entities[i]->position + globalPos;
      entities[i]->step(delta);
    }
  else
    progress += delta * speed;
}

void AnimatedCircleSection::render() {
  float scalar = animation.ease(progress);
  DrawCircleSector(globalPos + (Vector2){radius, radius}, radius, RAD2DEG * (centerAngle - offset * scalar), RAD2DEG * (centerAngle + offset * scalar), 12, colour);
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->render();
}

AnimatedCircleSectionLines::AnimatedCircleSectionLines(CircleSectionLines x, AnimatedWidget::easeType t) : CircleSectionLines(x) {
  animation = AnimatedWidget(t);
  progress = 0;
  speed = 1;
}

void AnimatedCircleSectionLines::step(float delta) {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++) {
      entities[i]->globalPos = entities[i]->position + globalPos;
      entities[i]->step(delta);
    }
  else
    progress += delta * speed;
}

void AnimatedCircleSectionLines::render() {
  float scalar = animation.ease(progress);
  DrawCircleSector(globalPos + (Vector2){radius, radius}, radius, RAD2DEG * (centerAngle - offset * scalar), RAD2DEG * (centerAngle + offset * scalar), 12, colour);
  DrawCircleSector(globalPos + (Vector2){radius, radius}, (radius - thickness), RAD2DEG * (centerAngle - offset * scalar), RAD2DEG * (centerAngle + offset * scalar), 12, BACKGROUND);
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->render();
}

AnimatedText::AnimatedText(Text x, AnimatedWidget::easeType t) : Text(x) {
  dimensions = MeasureTextEx(fonts[type], text.c_str(), size, 2) + (Vector2){0, 30};
  animation = AnimatedWidget(t);
  progress = 0;
  speed = 1;
}

void AnimatedText::step(float delta) {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++) {
      entities[i]->globalPos = entities[i]->position + globalPos;
      entities[i]->step(delta);
    }
  else
    progress += delta * speed;
}

void AnimatedText::render() {
  float scalar = animation.ease(progress);
  unsigned index = floor(scalar * text.length());
  char old = text[index];
  text[index] = '\0';
  DrawTextEx(fonts[type], text.c_str(), globalPos - dimensions / (Vector2){2, 2}, size, 2, col);
  text[index] = old;
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->render();
}

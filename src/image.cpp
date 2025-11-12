#include "image.hpp"
#include "animatedWidgets.hpp"
#include "include.h"
#include "widget.hpp"
#include <iostream>
#include <string>

ImageWidget::ImageWidget(Texture s, Vector2 p) {
  position = p;
  source = s;
  dimensions = {
    .x = (float)source.width,
    .y = (float)source.height
  };
  crop = {
    0,
    0,
    0,
    0
  };
  scale = 1;
}

ImageWidget::ImageWidget(std::string s, Vector2 p) {
  position = p;
  source = LoadTexture(s.c_str());
  dimensions = {
    .x = (float)source.width,
    .y = (float)source.height
  };
  crop = {
    0,
    0,
    0,
    0,
  };
  scale = 1;
}

ImageWidget::ImageWidget(char* s, Vector2 p) {
  position = p;
  source = LoadTexture(s);
  dimensions = {
    .x = (float)source.width,
    .y = (float)source.height
  };
  crop = {
    0,
    0,
    0,
    0
  };
  scale = 1;
}

ImageWidget::~ImageWidget() {
  UnloadTexture(source);
}

void ImageWidget::render() {
  DrawTexturePro(source, (Rectangle){
    crop.x,
    crop.y,
    (source.width - crop.width),
    (source.height - crop.height),
  }, (Rectangle){
    globalPos.y,
    globalPos.x,
    (source.width - crop.width) * scale,
    (source.height - crop.height) * scale,
  }, Vector2Zero(), 0, WHITE);
}

AnimatedImageWidget::AnimatedImageWidget(ImageWidget base, AnimatedWidget::easeType type) : ImageWidget(base) {
  dir = Right;
  animation = AnimatedWidget(type);
  progress = 0;
  dimensions = {
    .x = (float)source.width,
    .y = (float)source.height
  };
  scale = 1;
  speed = 1;
  crop = {
    0,
    0,
    0,
    0
  };
}

AnimatedImageWidget::AnimatedImageWidget(ImageWidget base, AnimatedWidget::easeType type, Direction d) : ImageWidget(base) {
  dir = d;
  animation = AnimatedWidget(type);
  progress = 0;
  speed = 1;
  scale = 1;
  dimensions = {
    .x = (float)source.width,
    .y = (float)source.height
  };
  crop = {
    0,
    0,
    0,
    0,
  };
}

AnimatedImageWidget::~AnimatedImageWidget() {
  UnloadTexture(source);
}

void AnimatedImageWidget::step(float delta) {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->process(delta);
  else
    progress += delta * speed;
}
void AnimatedImageWidget::render() {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->render();
  float scaleX = dir == Right || dir == Left ? animation.ease(progress) : 1;
  float scaleY = dir == Up || dir == Down ? animation.ease(progress) : 1;
  DrawTexturePro(source, (Rectangle){
    crop.x,
    crop.y,
    (source.width - crop.width) * scaleX,
    (source.height - crop.height) * scaleY,
  }, (Rectangle){
    globalPos.x,
    globalPos.y,
    (source.width - crop.width) * scale * scaleX,
    (source.height - crop.height) * scale * scaleY,
  }, Vector2Zero(), 0, WHITE);
}

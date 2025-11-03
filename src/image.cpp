#include "image.hpp"
#include "animatedWidgets.hpp"
#include "include.h"
#include <string>

ImageWidget::ImageWidget(Image s, Vector2 p) {
  position = p;
  source = LoadTextureFromImage(s);
  dimensions = {
    .x = (float)source.width,
    .y = (float)source.height
  };
}

ImageWidget::ImageWidget(std::string s, Vector2 p) {
  position = p;
  Image img = LoadImage(s.c_str());
  source = LoadTextureFromImage(img);
  UnloadImage(img);
  dimensions = {
    .x = (float)source.width,
    .y = (float)source.height
  };
}

ImageWidget::ImageWidget(char* s, Vector2 p) {
  position = p;
  Image img = LoadImage(s);
  source = LoadTextureFromImage(img);
  UnloadImage(img);
  dimensions = {
    .x = (float)source.width,
    .y = (float)source.height
  };
}

ImageWidget::~ImageWidget() {
  UnloadTexture(source);
}

void ImageWidget::render() {
  DrawTexturePro(source, (Rectangle){
    0,
    0,
    dimensions.x,
    dimensions.y,
  }, (Rectangle){
    position.x,
    position.y,
    dimensions.x,
    dimensions.y,
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
}

AnimatedImageWidget::AnimatedImageWidget(ImageWidget base, AnimatedWidget::easeType type, Direction d) : ImageWidget(base) {
  dir = d;
  animation = AnimatedWidget(type);
  progress = 0;
  dimensions = {
    .x = (float)source.width,
    .y = (float)source.height
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
    progress += delta;
}
void AnimatedImageWidget::render() {
  if(progress >= 1)
    for(int i = 0; i < entities.size(); i++)
      entities[i]->render();
  float scaleX = dir == Right || dir == Left ? animation.ease(progress) : 1;
  float scaleY = dir == Up || dir == Down ? animation.ease(progress) : 1;
  DrawTexturePro(source, (Rectangle){
    0,
    0,
    (float)source.width * scaleX,
    (float)source.height * scaleY,
  }, (Rectangle){
    position.x,
    position.y,
    (float)source.width * scaleX,
    (float)source.height * scaleY,
  }, Vector2Zero(), 0, WHITE);
}

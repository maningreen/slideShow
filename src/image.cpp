#include "image.hpp"
#include "animatedWidgets.hpp"
#include "include.h"
#include <string>

ImageWidget::ImageWidget(Image s, Vector2 p) {
  position = p;
  source = LoadTextureFromImage(s);
  dimensions = {
    (float)source.width,
    (float)source.height
  };
}

ImageWidget::ImageWidget(std::string s, Vector2 p) {
  position = p;
  Image img = LoadImage(s.c_str());
  source = LoadTextureFromImage(img);
  UnloadImage(img);
  dimensions = {
    (float)source.width,
    (float)source.height
  };
}

ImageWidget::ImageWidget(char* s, Vector2 p) {
  position = p;
  Image img = LoadImage(s);
  source = LoadTextureFromImage(img);
  UnloadImage(img);
  dimensions = {
    (float)source.width,
    (float)source.height
  };
}

ImageWidget::~ImageWidget() {
  UnloadTexture(source);
}

void ImageWidget::render() {
  DrawTextureV(source, position, WHITE);
}

AnimatedImageWidget::AnimatedImageWidget(ImageWidget base, AnimatedWidget::easeType type) : ImageWidget(base) {
  dir = Right;
  animation = AnimatedWidget(type);
}

AnimatedImageWidget::AnimatedImageWidget(ImageWidget base, AnimatedWidget::easeType type, Direction d) : ImageWidget(base) {
  dir = d;
  animation = AnimatedWidget(type);
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
  // DrawTexturePro(source, (Rectangle){
        // 0,
        // 0,
        // scaleX * source.width,
        // scaleY * source.height,
      // }, (Rectangle){
        // position.x,
        // position.y,
        // scaleX * source.width,
        // scaleY * source.height,
      /* // }, Vector2Zero(), 0, WHITE); */
}

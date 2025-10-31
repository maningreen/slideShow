#include "animatedWidgets.hpp"
#include "engine/entity.hpp"
#include "include.h"
#include "widget.hpp"

void init(Entity* root) {
  Rect* x = new Rect(100, 100, 100, 100, WHITE);
  Rect* y = new Rect(100, 100, 100, 100, GREEN);
  CircleSection* z = new CircleSection((Vector2){100, 100}, 50, PI, PI / 2, GREEN);
  Circle* w = new Circle((Vector2){100, 100}, 10, BLUE);
  Circle* f = new Circle((Vector2){100, 100}, 50, BLUE);
  Circle* g = new CircleSectionLines((Vector2){100, 100}, 50, PI, PI / 2, 10, RED);
  AnimatedRect* animatedTest = new AnimatedRect(Rect(100, 100, 100, 100, BLUE), AnimatedWidget::In, Horizontal);
  AnimatedRect* test2 = new AnimatedRect(Rect(100, 0, 100, 100, BLUE), AnimatedWidget::Out, Horizontal);
  AnimatedCircle* test3 = new AnimatedCircle(Circle((Vector2){400, 200}, 100, BLUE), AnimatedWidget::InOut);
  AnimatedCircleSection* test4 = new AnimatedCircleSection(CircleSection((Vector2){200, 0}, 100, PI, 1, RED), AnimatedWidget::InOut);
  AnimatedCircleSectionLines* test5 = new AnimatedCircleSectionLines(CircleSectionLines((Vector2){390, 390}, 100, 3 * PI / 4, PI / 4, 10, GREEN), AnimatedWidget::InOut);
  animatedTest->entities.push_back(test2);
  animatedTest->entities.push_back(test3);
  animatedTest->entities.push_back(test4);
  animatedTest->entities.push_back(test5);
  Box* box = hBox({vBox({x, z, y}), w, f, g, animatedTest});
  root->addChild(box);
  root->addChild(animatedTest);
}

void preRendering(Entity* root) {
  ClearBackground(BACKGROUND);
}

void postRendering(Entity* root) {
  DrawFPS(0, 0);
}

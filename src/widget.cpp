#include "widget.hpp"
#include "engine/entity.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

Widget::Widget(Vector2 p, Vector2 dimensions)
    : Entity2D("Widget", p), dimensions(dimensions),
      globalPos((Vector2){0, 0}) {}

Widget::Widget(): Widget(Vector2Zero(), Vector2Zero()) {}

Widget::~Widget() {}

void Widget::process(float delta) {
  for(int i = 0; i < entities.size(); i++) {
    // entities[i].globalPos = entities[i].position + position;
  }
  step(delta);
}

void Widget::step(float delta) {}

Box::Box(int d, std::vector<Widget*> widgets) {
  dir = d;
  entities = widgets;
  position = Vector2Zero();
}

Box::~Box() {
}

void Box::step(float delta) {
  if(entities.empty()) {
    killDefered();
    return;
  }
  entities[0]->process(delta);
  entities[0]->position = position;
  for(int i = 1; i < entities.size(); i++) {
    entities[i]->position = position;
    if(dir == Vertical)
      entities[i]->position.y = entities[i - 1]->position.y + entities[i - 1]->dimensions.y;
    else
      entities[i]->position.x = entities[i - 1]->position.x + entities[i - 1]->dimensions.x;
  }
}

void Box::render() {
  entities[0]->render();
}

Box* hBox(std::vector<Widget*> x) {
  return (new Box(Box::Horizontal, x));
}

Rect::Rect(float x, float y, float w, float h, Color c) {
  position = { .x = x, .y = y };
  dimensions = { .x = w, .y = h };
  colour = c;
}

Rect::Rect(Vector2 p, Vector2 d, Color c) {
  position = p;
  dimensions = d;
  colour = c;
}

Rect::Rect(Rectangle x, Color c) {
  position = { .x = x.x, .y = x.y };
  dimensions = { .x = x.width, .y = x.height };
  colour = c;
}

void Rect::render() {
  DrawRectangle(position.x, position.y, dimensions.x, dimensions.y, WHITE);
}

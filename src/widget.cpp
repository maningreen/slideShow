#include "widget.hpp"
#include "engine/entity.hpp"
#include <algorithm>
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
  dimensions = Vector2Zero();
  entities[0]->process(delta);
  entities[0]->position = position;
  dimensions += entities[0]->dimensions;
  for(int i = 1; i < entities.size(); i++) {
    entities[i]->position = position;
    if(dir == Vertical) {
      entities[i]->position.y = entities[i - 1]->dimensions.y + entities[i - 1]->position.y;
      dimensions.y += entities[i]->dimensions.y;
      if(dimensions.x < entities[i]->dimensions.x)
        dimensions.x = entities[i]->dimensions.x;
    }
    else if (dir == Horizontal){
      dimensions.x += entities[i]->dimensions.x;
      entities[i]->position.x = entities[i - 1]->dimensions.x + entities[i - 1]->position.x;
      if(dimensions.y < entities[i]->dimensions.y)
        dimensions.y = entities[i]->dimensions.y;
    }
  }
}

void Box::render() {
  for(int i = 0; i < entities.size(); i++)
    entities[i]->render();
}

Box* hBox(std::vector<Widget*> x) {
  return (new Box(Box::Horizontal, x));
}

Box* vBox(std::vector<Widget*> x) {
  return (new Box(Box::Vertical, x));
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
  DrawRectangle(position.x, position.y, dimensions.x, dimensions.y, colour);
}

Circle::Circle(Vector2 p, float r, Color c) {
  position = p;
  radius = r;
  colour = c;
  dimensions = {radius * 2, radius * 2};
}

void Circle::render() {
  DrawCircleV(position + (Vector2){radius, radius}, radius, colour);
}

CircleSection::CircleSection(Vector2 p, float r, float a, float b, Color c) : Circle(p, r, c) {
  centerAngle = a;
  offset = b;
}

void CircleSection::render() {
  DrawCircleSector(position + (Vector2){radius, radius}, radius, RAD2DEG * (centerAngle - offset), RAD2DEG * (centerAngle + offset), 12, colour);
}

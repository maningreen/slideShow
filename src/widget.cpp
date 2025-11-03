#include "widget.hpp"
#include "engine/entity.hpp"
#include "include.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

Widget::Widget(Vector2 p, Vector2 dimensions)
    : Entity2D("Widget", p), dimensions(dimensions),
      globalPos((Vector2){0, 0}) {}

Widget::Widget() : Widget(Vector2Zero(), Vector2Zero()) {}

Widget::~Widget() {}

void Widget::process(float delta) {
  for(int i = 0; i < entities.size(); i++) {
    entities[i]->step(delta);
    entities[i]->globalPos = entities[i]->position + position;
  }
  step(delta);
}

void Widget::death() {
  for(int i = 0; i < entities.size(); i++) {
    entities[i]->kill();
    entities.pop_back();
  }
}

void Widget::step(float delta) {}

Box::Box(Orientation d, std::vector<Widget*> widgets) {
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
    entities[i]->process(delta);
    entities[i]->position = position;
    if(dir == Vertical) {
      entities[i]->position.y = entities[i - 1]->dimensions.y + entities[i - 1]->position.y;

      dimensions.y += entities[i]->dimensions.y;
      if(dimensions.x < entities[i]->dimensions.x)
        dimensions.x = entities[i]->dimensions.x;
    }
    else if (dir == Horizontal) {
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
  return (new Box(Horizontal, x));
}

Box* vBox(std::vector<Widget*> x) {
  return (new Box(Vertical, x));
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
  DrawRectangle(globalPos.x, globalPos.y, dimensions.x, dimensions.y, colour);
}

Spacer::Spacer(float a, float b, float c, float d) : Rect(a, b, c, d, TRANSPARENT) {}
Spacer::Spacer(Vector2 a, Vector2 b) : Rect(a, b, TRANSPARENT) {}
Spacer::Spacer(Rectangle a) : Rect(a, TRANSPARENT) {}

Circle::Circle(Vector2 p, float r, Color c) {
  position = p;
  radius = r;
  colour = c;
  dimensions = {radius * 2, radius * 2};
}

Circle::Circle(float x, float y, float r, Color c) {
  position = {
    x,
    y
  };
  radius = r;
  colour = c;
  dimensions = {radius * 2, radius * 2};
}

void Circle::render() {
  DrawCircleV(globalPos + (Vector2){radius, radius}, radius, colour);
}

CircleSection::CircleSection(Vector2 p, float r, float a, float b, Color c) : Circle(p, r, c) {
  centerAngle = a;
  offset = b;
  dimensions = {
    .x = radius * 2,
    .y = radius * 2
  };
}

void CircleSection::render() {
  DrawCircleSector(globalPos + (Vector2){radius, radius}, radius, RAD2DEG * (centerAngle - offset), RAD2DEG * (centerAngle + offset), 12, colour);
}

CircleSectionLines::CircleSectionLines(Vector2 p, float r, float centerTheta, float offsetTheta, float t, Color c): CircleSection(p, r, centerTheta, offsetTheta, c) {
  thickness = t;
  dimensions = {
    .x = radius * 2,
    .y = radius * 2
  };
}
void CircleSectionLines::render() {
  Vector2 center = globalPos + (Vector2){radius, radius};
  DrawCircleSector(center, radius, RAD2DEG * (centerAngle - offset), RAD2DEG * (centerAngle + offset), 12, colour);
  DrawCircleSector(center, (radius - thickness), RAD2DEG * (centerAngle - offset), RAD2DEG * (centerAngle + offset), 12, BACKGROUND);
}

Font Text::fonts[0];

void Text::loadFonts() {
  fonts[0] = LoadFontEx("resources/body.ttf", 128, 0, 250); 
}

Text::Text(std::string x, fontType y, unsigned s, Vector2 p, Color c) {
  dimensions = MeasureTextEx(fonts[y], x.c_str(), s, 2);
  position = p - dimensions / (Vector2){2, 2};
  text = x;
  type = y;
  size = s;
  col = c;
}

Text::Text(std::string x, fontType y, unsigned s, Vector2 p, Vector2 dems) {
  position = p - MeasureTextEx(fonts[y], x.c_str(), s, 2) / (Vector2){2, 2};
  text = x;
  type = y;
  size = s;
  col = WHITE;
  dimensions = dems;
}

Text::Text(std::string x, fontType y, unsigned s, Vector2 p, Vector2 dems, Color c) {
  position = p - MeasureTextEx(fonts[y], x.c_str(), s, 2) / (Vector2){2, 2};
  text = x;
  type = y;
  size = s;
  col = c;
  dimensions = dems;
}

Text::~Text() {}

void Text::render() {
  DrawTextEx(fonts[type], text.c_str(), globalPos, size, 2, col);
}

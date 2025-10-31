#ifndef widget_h
#define widget_h

#include "engine/entity.hpp"
#include "include.h"
#include <climits>
#include <string>
#include <vector>

enum fontType {
  body = 0
};

struct Widget : Entity2D {
  Vector2 dimensions;
  Vector2 globalPos;

  virtual void step(float delta);
  void process(float delta) override;
  void death() override;

  std::vector<Widget*> entities;

  Widget(Vector2 p, Vector2 dimensions);
  Widget();
  ~Widget();
};

// a container widget 
// `position`s are ignored.
// a "functional" class.
// use:
//  hBox(Widget());
// stacks items on top of another.
struct Box : Widget {
  Box(Direction dir, std::vector<Widget*>);
  ~Box();

  void step(float delta) override;
  void render() override;

  private:
    // the direction in which to order things
    Direction dir;
};

struct Rect : Widget {
  void render() override;

  Color colour;

  Rect(Rectangle, Color);
  Rect(Vector2, Vector2, Color);
  Rect(float, float, float, float, Color);
};

struct Spacer : Rect {
  Spacer(Rectangle);
  Spacer(Vector2, Vector2);
  Spacer(float, float, float, float);
};

struct Circle : Widget {
  float radius;
  Color colour;
  Circle(Vector2 p, float r, Color c);
  void render() override;
};

// this class follows *radians*
struct CircleSection : Circle {
  CircleSection(Vector2 p, float r, float centerTheta, float offsetTheta, Color c);
  float centerAngle;
  float offset;
  void render() override;
};

struct CircleSectionLines : CircleSection {
  CircleSectionLines(Vector2 p, float r, float centerTheta, float offsetTheta, float thickness, Color c);
  float thickness;
  void render() override;
};

Box* hBox(std::vector<Widget*> widgets);
Box* vBox(std::vector<Widget*> widgets);

struct Text : Widget {
  std::string text;
  fontType type;
  Text(std::string x, fontType y, Vector2 position, Vector2 dems);
  ~Text();

  void render() override;

  static Font fonts[];
  static void loadFonts();
};

#endif

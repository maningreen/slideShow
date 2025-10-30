#ifndef widget_h
#define widget_h

#include "engine/entity.hpp"
#include <climits>
#include <vector>

struct Widget : Entity2D {
  Vector2 dimensions;
  Vector2 globalPos;

  virtual void step(float delta);
  void process(float delta) override;

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
  Box(int dir, std::vector<Widget*>);
  ~Box();

  void step(float delta) override;
  void render() override;
  
  enum Direction {
    Vertical,
    Horizontal
  };

  private:
    // the direction in which to order things
    int dir;
};

struct Rect : Widget {
  void render() override;

  Color colour;

  Rect(Rectangle, Color);
  Rect(Vector2, Vector2, Color);
  Rect(float, float, float, float, Color);
};

Box* hBox(std::vector<Widget> widgets);
// static vBox vBox(Widget widgets[]);

#endif

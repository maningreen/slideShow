#ifndef example_h
#define example_h

#include "engine/entity.hpp"

class Example : public Entity2D {
public:
  void render() override;
  void process(float delta) override;

  Example();
  ~Example();
};

#endif

#ifndef root_h
#define root_h

#include "entity.hpp"

class Root : public Entity {
private:
  void manageChildrenRendering(Entity* en);

  void manageChildrenProcesses(Entity* en, float delta);
public:
  Root();
  ~Root();

  // RenderTexture renderTexture;

  void process(float delta) override;
  void render() override;
  void postRender() override;

  static const Vector2 windowDimensions;
  static const std::string windowName;
};

#endif

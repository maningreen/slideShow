#include "root.hpp"
#include "entity.hpp"
#include <string>

const Vector2 Root::windowDimensions = {1920, 1080};
const std::string Root::windowName = "cool presentation thing!";

Root::Root() : Entity("root", nullptr) {}

Root::~Root() {
  CloseWindow();
}

void Root::process(float delta) {
  if(WindowShouldClose())
    killDefered();
  for(Entity* en : children)
    manageChildrenProcesses(en, GetFrameTime());
}

void Root::render() {
  BeginDrawing();
  for(Entity* child : children)
    manageChildrenRendering(child);
}

void Root::postRender() {
  EndTextureMode();

  // DrawTexturePro(renderTexture.texture, (Rectangle){0, 0, windowDimensions.x, -windowDimensions.y}, (Rectangle){0, 0, (float)GetScreenWidth(), -(float)GetScreenHeight()}, {0, 0}, 0, WHITE);

  EndDrawing();
}

void Root::manageChildrenRendering(Entity* en) {
  en->render();
  for(int i = 0; i < en->children.size(); i++)
    manageChildrenRendering(en->children[i]);
  en->postRender();
}

void Root::manageChildrenProcesses(Entity* en, float delta) {
  en->process(delta);
  for(int i = 0; i < en->children.size(); i++)
    manageChildrenProcesses(en->children[i], 1);
  if(!en->getValid())
    en->kill();
}

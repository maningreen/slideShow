#include "entity.hpp"
#include "root.hpp"
#include "../widget.hpp"

void init(Entity* root);

void preRendering(Entity* root);

void postRendering(Entity* root);

int main() {
  InitWindow(1920, 1080, "cool as heck website :sunglasses:");
  SetTargetFPS(60);

  Root* root = nullptr;

  root = new Root();
  Entity::setRoot(root);


  BeginDrawing();
  DrawCircle(0, 0, 50, WHITE);
  EndDrawing();

  while(!IsWindowReady());

  init(root);

  Text::loadFonts();

  while(!WindowShouldClose()) {

    root->process(0);

    preRendering(root);

    root->render();

    postRendering(root);

    root->postRender();
  }
  CloseWindow();
}

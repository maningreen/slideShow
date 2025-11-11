#include "entity.hpp"
#include "root.hpp"
#include "../widget.hpp"
#include <iostream>

void init(Entity* root);

void preRendering(Entity* root);

void postRendering(Entity* root);

int main() {

  std::cout << "test\n";

  InitWindow(1920, 1080, "balls");
  SetTargetFPS(60);

  Root* root = nullptr;

  root = new Root();
  Entity::setRoot(root);

  init(root);

  Text::loadFonts();

  BeginDrawing();
  DrawCircle(0, 0, 50, WHITE);
  EndDrawing();

  while(!WindowShouldClose()) {

    root->process(0);

    preRendering(root);

    root->render();

    postRendering(root);

    root->postRender();
  }
  CloseWindow();
}

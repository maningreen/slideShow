#include "entity.hpp"
#include "root.hpp"

void init(Entity* root);

void preRendering(Entity* root);

void postRendering(Entity* root);

int main() {
  Root* root = new Root();

  Entity::setRoot(root);

  init(root);

  while(root->getValid()) {

    root->process(0);

    preRendering(root);

    root->render();

    postRendering(root);

    root->postRender();
  }
}

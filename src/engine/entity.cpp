#include "entity.hpp"
#include "../include.h"
#include <string>
#include <vector>
#include <iostream>

Entity* Entity::root = nullptr;

bool Entity::setRoot(Entity* r) {
  if(root != nullptr)
    return false;
  root = r;
  return true;
}

Entity* Entity::getRoot() {
  return root;
}

Entity2D::Entity2D(const std::string& name, Entity* par, Vector2 position) : Entity(name, par), position(position) {}

Entity2D::Entity2D(const std::string& name, Vector2 position) : Entity(name), position(position) {}

Entity::~Entity() {}

Entity::Entity(const std::string& name, Entity* parent) : parent(parent), name(name), valid(true) {}

Entity::Entity(const std::string& name) : parent(nullptr), name(name), valid(true) {}

void Entity::addChild(Entity* child) {
  child->parent = this;
  child->init();
  children.push_back(child);
}

void Entity::addTag(std::string tag) {
  tags.push_back(tag);
}

Entity* Entity::getParent() {
  return parent;
}

bool Entity::removeTag(std::string tag) {
  for(int i = 0; i < tags.size(); i++)
    if(tags[i] == tag) {
      tags[i] = tags.back();
      tags.pop_back();
      return true;
    }
  return false;
}

bool Entity::hasTag(std::string tag) {
  for(int i = 0; i < tags.size(); i++)
    if(tags[i] == tag)
      return true;
  return false;
}

void Entity::printAllChildren() {
  //so, what we wants to do here is print a bunch of sthuff, in particular all of the children *recursively*
  std::cout << name << '\n';
  for(Entity* child : children) {
    child->printAllChildren();
  }
}

int Entity::getEntityIndex(Entity* entity) {
  for(int i = 0; i < children.size(); i++)
    if(children[i] == entity)
      return i;
  return -1;
}

void Entity::kill() {
  death();
  while(!children.empty()) {
    children.back()->kill();
    children.pop_back();
  }
  delete this;
}

bool Entity::getValid() {
  return valid;
}

void Entity::killDefered() {
  valid = false; // :p
}

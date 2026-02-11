
#pragma once
#include "Item.h"

#include <memory>
#include <vector>
struct DrawContext {
  float scale = 1.0f;
  Vector2 offset = {0, 0};
};
class Property {
private:
  bool dragging = false;
  Vector2 dragOffset{0, 0};

public:
  Property();
  ItemData *getSelected();
  std::vector<std::unique_ptr<ItemData>> items;

  int selected = -1;

  void MoveForward();
  void MoveBackward();

  void AddImage(std::string path);
  void AddText(std::string path);
  void DrawGui();
  void Draw(int id, const DrawContext &ctx);
  bool UpdateInput(Vector2 mouse);
};

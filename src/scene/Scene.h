#pragma once
#include "../property/Property.h"

class Scene {
public:
  std::string name = "Scene";
  Color background = {5, 6, 10, 255};
  Property property;
  Scene();
  ~Scene();

  RenderTexture2D texRend;
  bool dirty = false;
  void DrawThumbnail(int posX, int posY);
  void GenerateThumbnail(const DrawContext &ctx);
  void DrawGui();
};

#include "Scene.h"
#include <iostream>
Scene::Scene() {
  texRend = LoadRenderTexture(192, 192);
}
Scene::~Scene() {
  if (texRend.id != 0) UnloadRenderTexture(texRend);
  std::cout << "scene destroyed\n";
}
void Scene::DrawThumbnail(int posX, int posY) {
  DrawTexture(texRend.texture, posX, posY, WHITE);
}
void Scene::GenerateThumbnail(const DrawContext &ctxThumbnail) {
  BeginTextureMode(texRend);
  Color bg = (Color){40, 40, 40, 255};
  property.Draw(0, ctxThumbnail);
  EndTextureMode();
}

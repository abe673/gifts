#pragma once

#include "Scene.h"

class SceneManager {
public:
  std::vector<std::unique_ptr<Scene>> scenes;
  SceneManager();
  Scene *GetActive();
  Scene *Get(int index);
  int GetActiveIndex() const;
  Scene *CreateScene(const std::string &name);
  void RemoveScene(int index);
  void SetActive(int index);

  void DrawGui();
  void Draw(int winid);
  void Update(int winid);

  Vector2 targetResolution = {1280, 720};
  int activeScene = -1;

  DrawContext ctxNormal;
  DrawContext ctxDisplay;
  DrawContext ctxEditor;
  DrawContext ctxThumbnail;
  void CalculateCtx();

private:
};

inline SceneManager &GetSM() {
  static SceneManager sm;
  return sm;
}

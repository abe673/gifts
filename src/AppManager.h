
#pragma once
#include "scene/SceneManager.h"
#include "window/WindowManager.h"

class AppManager {
private:
  WindowManager &windows;
  SceneManager &scenes;

public:
  AppManager();
  // Resolusi target untuk semua scene
  Vector2 targetResolution = {1920, 1080};

  // Inisialisasi semua subsistem
  void Init();

  // Update per-frame
  void Update();

  // Render per-frame
  void Draw();

  // Mengakses WindowManager / SceneManager jika perlu
  WindowManager &GetWindows() {
    return windows;
  }
  SceneManager &GetScenes() {
    return scenes;
  }
};

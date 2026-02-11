#pragma once
#include "Window.h"
#include "raylib.h"
#include <memory>

struct WindowManager {
  WindowManager();
  std::unique_ptr<Window> appWindow[(int)WinID::Count];
  Window *GetWindow(WinID id);
  void Start(WinID winId);
  const Rectangle &GetRect(WinID id) const;
  void CloseForce(WinID id);
  Rectangle rects[(int)WinID::Count];
  void SaveScreenRect();
  void LoadScreenRect();
};

inline WindowManager &GetWindowManager() {
  static WindowManager wm;
  return wm;
}


#include "WindowManager.h"
#include "raylib.h"
#include <fstream>
#include <memory>
WindowManager::WindowManager() {
  rects[(int)WinID::Editor] = {10, 50, 300, 200};
  rects[(int)WinID::Display] = {310, 50, 300, 200};
  LoadScreenRect(); // isi dari JSON kalau ada
}
void WindowManager::SaveScreenRect() {
  std::ofstream file("layout.bin", std::ios::binary);
  if (!file.is_open()) return;

  file.write(reinterpret_cast<char *>(rects), sizeof(Rectangle) * 2);
}

void WindowManager::LoadScreenRect() {
  std::ifstream file("layout.bin", std::ios::binary);
  if (!file.is_open()) return;

  file.read(reinterpret_cast<char *>(rects), sizeof(Rectangle) * 2);
}
const Rectangle &WindowManager::GetRect(WinID id) const {
  return rects[(int)id];
};
Window *WindowManager::GetWindow(WinID id) {
  return appWindow[(int)id].get();
}
void WindowManager::Start(WinID winId) {
  int i = (winId == WinID::Editor) ? 0 : 1;
  if (!appWindow[i]) {
    appWindow[i] = std::make_unique<Window>();
    appWindow[i]->Start(winId, &rects[i]);
  }
}

void WindowManager::CloseForce(WinID id) {
  int i = (int)id;
  if (!appWindow[i]) return;
  if (appWindow[i]->open) {
    appWindow[i]->Activate();
    appWindow[i]->gpu.DestroyAll();
    CloseWindow();
    appWindow[i]->open = false;
  }
  SaveScreenRect();
  appWindow[i].reset(); // ← lifecycle selesai
}

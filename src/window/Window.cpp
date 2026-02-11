
#include "Window.h"
#include "raylib.h"

Window::Window() {
}
void Window::Activate() {
  SetActiveWindowContext(contextId);
}
bool Window::ShouldClose() const {
  return WindowShouldClose();
}

void Window::Start(WinID _id, Rectangle *_screenRect) {
  if (open) return;
  idWin = _id;
  rect = _screenRect;
  contextId = InitWindowPro(rect->width, rect->height, _id == WinID::Editor ? "control" : "display", FLAG_WINDOW_RESIZABLE);
  Activate();
  SetTargetFPS(60);
  SetExitKey(KEY_NULL);
  FindMonitor();
  open = true;
}

void Window::FindMonitor() {
  float x, y, w, h;
  Activate();

  if (GetMonitorCount() > 1 && idWin == WinID::Display) {
    //    std::cout << "find a second monitor\n";
    Vector2 mpos = GetMonitorPosition(1);
    x = mpos.x;
    y = mpos.y;
    w = GetMonitorWidth(1);
    h = GetMonitorHeight(1);
    MonitorRect = (Rectangle){x, y, w, h};
    rect->x = x;
    rect->y = y;
    rect->height = h;
    rect->width = w;
    ToggleFullscreen();
  } else {
    Vector2 mpos = GetMonitorPosition(0);
    x = mpos.x;
    y = mpos.y;
    w = GetMonitorWidth(0);
    h = GetMonitorHeight(0);
    MonitorRect = (Rectangle){x, y, w, h};
    SetWindowPosition(rect->x, rect->y);
  }
}

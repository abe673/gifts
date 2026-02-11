#include "LoopEngine.h"
#include "../window/WindowManager.h"
#include "rlImGui.h"
#include "setupImGui.h"
#include <queue>

enum class TypeEngineEvent { None, StartDisplayWindow, CloseDisplayWindow, CloseAllWindow, FindAndFit };

struct Engine_Event {
  TypeEngineEvent type;
  Engine_Event(TypeEngineEvent _type) : type(_type) {
  }
};

static WindowManager &WM = GetWindowManager();
static std::queue<Engine_Event> q;
static bool isRunning = false;

void EngineOnGui() {

  ImGui::Text("FPS %d", GetFPS());
  ImGui::SameLine();
  if (EngineDisplayIsOpen()) {
    if (ImGui::Button(ICON_FA_EYE)) EngineCloseDisplay();
  } else {
    if (ImGui::Button(ICON_FA_EYE_SLASH)) EngineOpenDisplay();
  }
  ImGui::SameLine();
  if (ImGui::Button(ICON_FA_DESKTOP)) {
    EngineFindMonitorAndFit();
  }
  ImGui::SameLine();
  if (ImGui::Button(ICON_FA_POWER_OFF)) {
    EngineClose();
  }
}

bool EngineDisplayIsOpen() {
  Window *win = WM.GetWindow(WinID::Display);
  return win ? win->open : false;
}

bool EngineGuiBegin(WinID id) {
  if (id != WinID::Editor) return false;
  rlImGuiBegin();
  DrawDockSpace();
  return true;
};

void EngineGuiEnd() {
  rlImGuiEnd();
};

void EngineCloseDisplay() {
  q.push(Engine_Event(TypeEngineEvent::CloseDisplayWindow));
};
void EngineOpenDisplay() {
  q.push(Engine_Event(TypeEngineEvent::StartDisplayWindow));
};
void EngineClose() {
  q.push(Engine_Event(TypeEngineEvent::CloseAllWindow));
};
void EngineFindMonitorAndFit() {
  q.push(Engine_Event(TypeEngineEvent::FindAndFit));
};

void EngineUpdate() {
  while (!q.empty()) {
    Engine_Event e = q.front();
    q.pop();
    switch (e.type) {
    case TypeEngineEvent::CloseAllWindow:
      WM.CloseForce(WinID::Display);
      WM.CloseForce(WinID::Editor);
      isRunning = false;
      break;
    case TypeEngineEvent::CloseDisplayWindow:
      WM.CloseForce(WinID::Display);
      break;
    case TypeEngineEvent::StartDisplayWindow:
      WM.Start(WinID::Display);
      WM.GetWindow(WinID::Editor)->Activate();
      MinimizeWindow();
      RestoreWindow();
      break;
    case TypeEngineEvent::FindAndFit: {
      WM.GetWindow(WinID::Editor)->FindMonitor();
      if (!WM.GetWindow(WinID::Display)) WM.Start(WinID::Display);
      WM.GetWindow(WinID::Display)->FindMonitor();
      break;
    }

    default:
      break;
    }
  }
};

bool &EngineIsRunning() {
  return isRunning;
}

void EngineInit() {
  if (!EngineIsRunning()) {
    SetTraceLogLevel(LOG_ERROR);
    WM.Start(WinID::Editor);
    // WM.Start(WinID::Display);
    isRunning = true;

    rlImGuiSetup(true);
    setupGui(); // optional theme
  }
}

bool EngineBegin(WinID id) {
  Window *win = WM.GetWindow(id);
  if (!win) return false;
  win->Activate();
  if (win->ShouldClose()) {
    if ((WinID)id == WinID::Editor)
      EngineClose();
    else
      EngineCloseDisplay();
    return false;
  }

  if (IsWindowResized()) {
    win->rect->x = GetWindowPosition().x;
    win->rect->y = GetWindowPosition().y;
    win->rect->width = GetScreenWidth();
    win->rect->height = GetScreenHeight();
  }

  BeginDrawing();
  return true;
}

void EngineEnd(int id) {
  EndDrawing();
}

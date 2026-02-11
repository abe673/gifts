

#include "SceneManager.h"
#include "../window/WindowManager.h"
SceneManager::SceneManager() {
  scenes.reserve(50);
  // CreateScene("Default");
  // activeScene = 0;
}

Scene *SceneManager::GetActive() {
  if (activeScene < 0 || activeScene >= scenes.size()) return nullptr;
  return scenes[activeScene].get();
}

Scene *SceneManager::Get(int index) {
  if (index < 0 || index >= scenes.size()) return nullptr;
  return scenes[index].get();
}

int SceneManager::GetActiveIndex() const {
  return activeScene;
}

Scene *SceneManager::CreateScene(const std::string &name) {
  auto sc = std::make_unique<Scene>();
  sc->name = name;
  scenes.push_back(std::move(sc));
  activeScene = scenes.size() - 1;
  return scenes.back().get();
}

void SceneManager::RemoveScene(int index) {
  if (index < 0 || index >= scenes.size()) return;

  scenes.erase(scenes.begin() + index);

  if (activeScene >= scenes.size()) activeScene = scenes.empty() ? -1 : 0;
}

void SceneManager::SetActive(int index) {
  if (index >= 0 && index < scenes.size()) activeScene = index;
}

void SceneManager::Draw(int winid) {
  if (Scene *s = GetActive()) {
    ClearBackground(s->background);
    DrawContext &ctx = (winid == 0) ? ctxEditor : ctxDisplay;
    Rectangle view = (Rectangle){ctx.offset.x, ctx.offset.y, targetResolution.x * ctx.scale, targetResolution.y * ctx.scale};

    BeginScissorMode(view.x, view.y, view.width, view.height);
    s->property.Draw(winid, ctx);

    EndScissorMode();
    DrawRectangleLinesEx(view, 2, GRAY);
    // s->DrawThumbnail(30, 30);
  } else {
    ClearBackground({5, 6, 10, 255});
  }
}

void SceneManager::Update(int winid) {
  if (IsWindowResized()) {
    CalculateCtx();
  }
  if (winid != 0) return;
  if (!IsWindowFocused()) return;

  if (Scene *s = GetActive()) {
    Vector2 mouse = GetMousePosition();
    mouse.x = (mouse.x - ctxEditor.offset.x) / ctxEditor.scale;
    mouse.y = (mouse.y - ctxEditor.offset.y) / ctxEditor.scale;
    if (s->property.UpdateInput(mouse)) {
      s->dirty = true;
    };
  }
}

inline DrawContext GetScaleCtx(Vector2 cfrom, Vector2 cTo) {
  DrawContext r;
  float scaleX = cTo.x / cfrom.x;
  float scaleY = cTo.y / cfrom.y;

  r.scale = std::min(scaleX, scaleY);
  r.offset = {(cTo.x - cfrom.x * r.scale) * 0.5f, (cTo.y - cfrom.y * r.scale) * 0.5f};
  return r;
}

void SceneManager::CalculateCtx() {
  static const Rectangle &displayRect = GetWindowManager().GetRect(WinID::Display);
  static const Rectangle &editorRect = GetWindowManager().GetRect(WinID::Editor);
  ctxDisplay = GetScaleCtx(targetResolution, {displayRect.width, displayRect.height});
  ctxEditor = GetScaleCtx(targetResolution, (Vector2){editorRect.width, editorRect.height});
  ctxThumbnail = GetScaleCtx(targetResolution, {192, 192});
  TraceLog(LOG_INFO, "calculated");
}

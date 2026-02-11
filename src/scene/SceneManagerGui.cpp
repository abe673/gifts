#include "SceneManager.h"
#include "imgui.h"

void SceneManager::DrawGui() {
  ImGui::Text("activescene %d", activeScene);
  ImGui::Text("Scenes count %d", (int)scenes.size());
  ImGui::Text("target size %0.f %0.f", targetResolution.x, targetResolution.y);
  if (Scene *s = GetSM().GetActive()) {
    s->DrawGui();
  }
}

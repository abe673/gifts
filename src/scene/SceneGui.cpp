#include "Scene.h"
#include "imgui.h"

void Scene::DrawGui() {
  ImGui::Text("name %s", name.c_str());
  ImGui::Text("dirty %s", (dirty) ? "yes" : "no");
  property.DrawGui();
}

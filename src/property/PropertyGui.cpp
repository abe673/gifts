#include "Property.h"
#include "imgui.h"

void Property::DrawGui() {
  ImGui::SeparatorText("Property");
  ImGui::Text("item size %d", (int)items.size());
  ImGui::Text("selected %d", selected);
  ImGui::Text("dragging %s", (dragging) ? "yes" : "no");
  ImGui::Text("offset %0.f %0.f", dragOffset.x, dragOffset.y);

  if (ImGui::Button("move up")) MoveForward();
  if (ImGui::Button("move down")) MoveBackward();
}

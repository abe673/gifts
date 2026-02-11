#include "engine/LoopEngine.h"
#include "imgui.h"
#include "scene/SceneManager.h"
#include "window/WindowManager.h"

#include "raylib.h"

int main(int argc, char *argv[]) {
  EngineInit();
  SceneManager &sm = GetSM();

  sm.CreateScene("oke");
  sm.GetActive()->property.AddImage("asset/win.png");
  while (EngineIsRunning()) {
    for (int i = 0; i < 2; i++) {
      if (!EngineBegin((WinID)i)) continue;

      sm.Draw(i);
      if (EngineGuiBegin((WinID)i)) {

        ImGui::Begin("main");
        EngineOnGui();
        sm.DrawGui();
        if (ImGui::Button("addimage")) {
          sm.GetActive()->property.AddImage("asset/win.png");
        }
        if (ImGui::Button("add2img")) {
          sm.GetActive()->property.AddImage("asset/lose.png");
        }
        ImGui::End();
        EngineGuiEnd();
      }
      if (!ImGui::GetIO().WantCaptureMouse) {
        sm.Update(i);
      }

      EngineEnd(i);
    }

    EngineUpdate();
  }
  return 0;
}

#include "AppManager.h"

AppManager::AppManager() : windows(GetWindowManager()), scenes(GetSM()) {
}

void AppManager::Init() {
  // Contoh membuat scene default
  scenes.CreateScene("Default");
}

void AppManager::Update() {
}

void AppManager::Draw() {
}

#pragma once

#include "../context/RenderContext.h"
#include "raylib.h"
#include <cstdint>

enum class WinID : uint8_t { Editor = 0, Display = 1, Count };

class Window {
private:
  int contextId = -1;
  WinID idWin;

public:
  bool open = false;
  Rectangle *rect;
  Rectangle MonitorRect;
  RenderContext gpu;

  Window();
  void Activate();
  bool ShouldClose() const;
  void Start(WinID _id, Rectangle *_screenRect);
  void FindMonitor();
};

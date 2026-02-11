/*
Note: ini cuma ngurus basic runtime
      dan window open dan close
 */

#pragma once
#include "../window/Window.h"

void EngineInit();
bool &EngineIsRunning();
bool EngineBegin(WinID id);
void EngineEnd(int id);
void EngineClose();
void EngineUpdate();
void EngineOpenDisplay();
void EngineCloseDisplay();
bool EngineGuiBegin(WinID id);
void EngineGuiEnd();
bool EngineDisplayIsOpen();
void EngineOnGui();
void EngineFindMonitorAndFit();

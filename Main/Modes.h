#pragma once

enum RobotMode {
  MODE_MAZE,
  MODE_MANUAL,
  MODE_FIGHT
};

void initModes();
void updateMode();
RobotMode getMode();
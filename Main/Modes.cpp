#include "Modes.h"
#include "Controller.h"

static RobotMode currentMode = MODE_MAZE;

void initModes(){
  currentMode = MODE_MAZE;
}

void updateMode(){
}

RobotMode getMode(){
  return currentMode;
}
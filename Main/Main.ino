#include "Controller.h"
#include "Modes.h"
#include "Arm.h"

void setup() {
  Serial.begin(115200);

  initController();
}

void loop() {
  updateArm(); // DO NOT TOUCH THIS LINE !!! 
}
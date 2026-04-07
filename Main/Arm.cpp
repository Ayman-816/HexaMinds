#include <stdint.h>
#include "Arm.h"

Adafruit_PWMServoDriver PCA = Adafruit_PWMServoDriver();

// Offset Array
int offsets[3] = {0, 0, 0};

// Gripper Variables
uint32_t startTime = 0;
uint32_t Gripperduration = 800; // Calibrated till the gripper closes 
bool isRunning = false;

void setupPCA(){
  // Configs no body understands but chatgpt said so :)
  PCA.begin();
  PCA.setOscillatorFrequency(27000000);
  PCA.setPWMFreq(50);

  returnHome(); // Starting Position
  delay(10);
}

void moveArm(int S_angle, int W_angle, int G_speed){
  
}

/*
 Variables to calibrate " 1800, 1200, Gripperduration << Global Variable>>"
*/
void controlGripper(uint8_t state){
  if(!isRunning){
    if(state == 0){ // Close Gripper
      startTime = millis();
      isRunning = true;
      writeMicros(GRIPPER, 1800); // CCW
    }

    else if(state == 1){ // Open Gripper
      startTime = millis();
      isRunning = true;
      writeMicros(GRIPPER, 1200); // CW
    }
  }

  if (isRunning) {
    if (millis() - startTime >= Gripperduration) {
      writeMicros(GRIPPER, 1500 + offsets[GRIPPER]); // STOP
      isRunning = false;
    }
  }
}

void setOffset(int S_angle, int W_angle, int G_speed){
  offsets[SHOULDER] = angleToMicros(S_angle) - 1500;
  offsets[WRIST] = angleToMicros(W_angle) - 1500;
  offsets[GRIPPER] = G_speed; 
}

void returnHome(){
  //moveArm(); //Parameters after testing
}

int angleToMicros(int angle){
  int us = map(angle, 0, 180, 1000, 2000);
  return us;
}

void writeMicros(int channel, int us){
  uint32_t pulse = (uint32_t)us * 4096 / 20000;
  PCA.setPWM(channel, 0, pulse);
}
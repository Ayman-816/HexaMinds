#include "Arm.h"

Adafruit_PWMServoDriver PCA = Adafruit_PWMServoDriver();

// Offset Array
int offsets[3] = {0, 0, 0};

// Links Variables
int currentS = 90, targetS = 90;
int currentW = 90, targetW = 90;
uint32_t lastMoveTime = 0;
int moveInterval = 30; 

// Gripper Variables
uint32_t startTime = 0;
uint32_t duration = 800; // Calibrated ...... range :- 500 - 1500
bool active = false;

void setupPCA(){
  PCA.begin();
  PCA.setOscillatorFrequency(27000000);
  PCA.setPWMFreq(50);
  
  //Home position
  writeMicros(SHOULDER, angleToMicros(currentS));
  writeMicros(WRIST, angleToMicros(currentW));
}

void updateArm(){
  uint32_t now = millis();

  // Link Movement
  if(now - lastMoveTime >= (uint32_t)moveInterval){
    lastMoveTime = now;
    bool moved = false;

    if(currentS < targetS){ currentS++; moved = true; }
    else if(currentS > targetS) { currentS--; moved = true; }

    if(moved) writeMicros(SHOULDER, angleToMicros(currentS) + offsets[SHOULDER]);

    moved = false;
    if(currentW < targetW) { currentW++; moved = true; }
    else if(currentW > targetW) { currentW--; moved = true; }

    if(moved) writeMicros(WRIST, angleToMicros(currentW) + offsets[WRIST]);
  }

  // Gripper open / close without delay
  if(active){
    if(now - startTime >= duration){
      writeMicros(GRIPPER, 1500);
      active = false;
    }
  }
}

void moveArm(int S_angle, int W_angle, int speed){
  targetS = S_angle;
  targetW = W_angle;
  moveInterval = speed;
}

void controlGripper(uint8_t state){
  if(active) return;

  if(state == 0){ // Close
    writeMicros(GRIPPER, 1800 + offsets[GRIPPER]); 
  } 
  else{ // Open
    writeMicros(GRIPPER, 1200 + offsets[GRIPPER]);
  }
  
  startTime = millis();
  active = true;
}

void setOffset(int S_angle, int W_angle, int G_speed){
  offsets[SHOULDER] = angleToMicros(S_angle) - 1500;
  offsets[WRIST] = angleToMicros(W_angle) - 1500;
  offsets[GRIPPER] = G_speed; 
}

void returnHome(){
  moveArm(90, 90, 20); // Calibrated
}

int angleToMicros(int angle){
  return map(angle, 0, 180, 1000, 2000);
}

void writeMicros(int channel, int us){
  uint32_t pulse = (uint32_t)us * 4096 / 20000;
  PCA.setPWM(channel, 0, pulse);
}
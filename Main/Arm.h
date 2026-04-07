#pragma once

#include <stdint.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

enum ServoChannel {
  SHOULDER, // 0
  WRIST,    // 1
  GRIPPER   // 2
}; //As if u made 3 spearate #defines ya karim call them in the function no big deal :)

void setupPCA();
void writeMicros(int channel, int us);
void moveArm(int S_angle, int W_angle, int G_speed);
void controlGripper(uint8_t state); // 0 -> Close , 1 -> Open
void returnHome();
void setOffset(int S_angle, int W_angle, int G_speed);
int angleToMicros(int angle);


/*
How Will the ARM work :- 3 main movements 
  1st -> Move the arm down and open the gripper in one motion 
  2nd -> Move the arm up to lift the load
  3rd -> Open and close the gripper cuz i dont trust البصمجة

Additional functions :- 
  setupPCA      (initalize the I2C address)
  returnHome    (To return to home position DUHH!)
  moveArm     (Smooth movement of the servos via a loop so that the arm doesnt jitter :) )
  setOffset     (Line up the servos)
  angleToMicros (Convert microSeconds to angle to be easier to work with)

Servo Control Functions With PCA library:
  << writeMicros(channel, us) >> 
    1000us => 0 degrees for 180 servos, Full Speed CW for 360 servo
    1500us => 90 degrees for 180 servos, Stop for 360 servo
    2000us => 180 degrees for 180 servos, Full Speed CCW for 360 servo

  << setPWM(channel, on, off) >> مش عجباني
    channel: 0 -> 15 on the PCA
    on: The "tick" count when the pulse starts set this to 0
    off: The "tick" count when the pulse ends 0 -> 4095
         For 50Hz servos: 150 is usually 0 degrees, and 600 is usually 180 degrees
*/
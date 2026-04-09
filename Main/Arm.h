#pragma once

#include <stdint.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Servo Channel Mapping on PCA9685
enum ServoChannel {
  SHOULDER = 0, 
  WRIST    = 1,    
  GRIPPER  = 2   
}; 

// Core Functions
void setupPCA();
void updateArm(); // مهم فشخخخخخخ حطها ف أول اللووب و كمل شغلك عادي 
void writeMicros(int channel, int us);
int angleToMicros(int angle);
void moveArm(int S_angle, int W_angle, int speed);// speed range :- 20 - 60
void controlGripper(uint8_t state); // 0 -> Close , 1 -> Open
void returnHome();
void setOffset(int S_angle, int W_angle, int G_speed);



/*
How Will the ARM work :- 3 main movements 
  1st -> Move the arm down and open the gripper in one motion 
  2nd -> Move the arm up to lift the load
  3rd -> Open and close the gripper cuz i dont trust البصمجة

Additional functions :- 
  setupPCA      (initalize the I2C address)
  updateArm     (Crutial for non-blocking code must be put on top of the loop)
  angleToMicros (Convert microSeconds to angle to be easier to work with)
  returnHome    (To return to home position DUHH!)
  setOffset     (Line up the servos)
  
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
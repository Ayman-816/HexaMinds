#include "Arm.h"

Adafruit_PWMServoDriver PCA = Adafruit_PWMServoDriver();

void setupPCA(){
  // Configs no body understands but chatgpt said so :)
  PCA.begin();
  PCA.setOscillatorFrequency(27000000);
  PCA.setPWMFreq(50);

  returnHome(); // Starting Position
  delay(10);
}

void moveServo(int servo_channel,int angle){
  
}
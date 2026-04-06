#pragma once

// ================= I2C (PCA9685 + MPU6050) =================
#define I2C_SDA 21
#define I2C_SCL 22

// ================= ULTRASONIC SENSORS =================

// Front Sensor
#define US_FRONT_TRIG 32
#define US_FRONT_ECHO 14 

// Left Sensor
#define US_LEFT_TRIG 25
#define US_LEFT_ECHO 26  

// Right Sensor
#define US_RIGHT_TRIG 27
#define US_RIGHT_ECHO 33

// ================= MOTOR DRIVER (TB6612) =================

// Front Motors
#define MOTOR_F_PWM   18
#define MOTOR_F_IN1   19
#define MOTOR_F_IN2   23

// Rear Motors
#define MOTOR_R_PWM   5
#define MOTOR_R_IN1   17
#define MOTOR_R_IN2   16

// ================= OPTIONAL / FUTURE =================
#define FREE_1 4
#define FREE_2 13

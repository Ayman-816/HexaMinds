#pragma once
#include <FastLED.h>

// Configuration
#define LED_PIN     13
#define NUM_LEDS    16
#define BRIGHTNESS  150  // 60% Power

void initLEDs();
void updateLEDs();

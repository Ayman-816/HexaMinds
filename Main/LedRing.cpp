#include "LED_Module.h"
#include "PS5_Module.h" 

CRGB leds[NUM_LEDS];
uint8_t color = 0;
unsigned long lastLEDMove = 0;
const int ledInterval = 33;

void initLEDs(){
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void updateLEDs(){
  uint32_t now = millis();

  if(now - lastLEDMove >= (uint32_t)ledInterval) {
    lastLEDMove = now;
    
    if(!ps5.isConnected()){
      uint8_t breath = beatsin8(30, 60, 255);
      fill_solid(leds, NUM_LEDS, CRGB::Red);
      FastLED.setBrightness(map(breath, 0, 255, 0, BRIGHTNESS));
    }
    /*if u need to add any other indicators using the ring light put the ps5 controller condition in an 
      else if statement and wirte your color like the example below :) أي خدعه*/

    /*else if(ps5.Square()) {
      FastLED.setBrightness(BRIGHTNESS);
      fill_rainbow(leds, NUM_LEDS, color++, 7);
    }*/
    
    else{
      FastLED.setBrightness(BRIGHTNESS);
      fill_solid(leds, NUM_LEDS, CRGB::Cyan);
    }
    FastLED.show();
  }
}
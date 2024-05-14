//==========================================================================
// Moire Clock - LEDs.cpp
//
// Copyright (c) 2024, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#include "LEDs.h"
#include <FastLED.h>
#include "hardware.h"

FASTLED_USING_NAMESPACE

uint8_t gHue = 0; // rotating "base color" used by many of the patterns
CRGB leds[NUM_LEDS];

void InitLEDs() {
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,LED_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

void lightLED(int iLED) {
  
  FastLED.clear(); 
  leds[iLED] = CHSV(gHue, 255, 255);
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  

}

  
void cycleAllLEDs()
{
  // Call the current pattern function once, updating the 'leds' array
  //Patterns[gCurrentPatternNumber]();
  fill_solid(leds, NUM_LEDS, CHSV(gHue, 255, 255));

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 50 ) { gHue++; } // slowly cycle the "base color" through the rainbow
}




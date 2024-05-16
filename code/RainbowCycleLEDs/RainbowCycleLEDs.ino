#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    20

#define BRIGHTNESS         255
#define FRAMES_PER_SECOND  120

const int LED_PIN = 2;          

#include <FastLED.h>

FASTLED_USING_NAMESPACE

uint8_t gHue = 0; // rotating "base color" used by many of the patterns
CRGB leds[NUM_LEDS];

void setup() {
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,LED_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
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

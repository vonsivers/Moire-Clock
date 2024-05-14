//==========================================================================
// Moire Clock - LEDs.h
//
// Copyright (c) 2024, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#ifndef LEDS_H
#define LEDS_H

#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    20

#define BRIGHTNESS         255
#define FRAMES_PER_SECOND  120

const int hoursLED = 7;
const int tomLED = 14;
const int minsLED = 9;

void InitLEDs();
void lightLED(int iLED);
void cycleAllLEDs();

#endif //LEDS_H
//==========================================================================
// Moire Clock - ClockCoordinates.cpp
//
// Copyright (c) 2024, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================
#include <arduino.h>
#include <avr/pgmspace.h> 
#include "ClockCoordinates.h"
#include "stepper.h"

// calculate absolute position in steps 
long GetDigitSteps(int iTime, int digit) {

  switch (iTime) {
    case MINUTES :
      return MINUTES_POS[digit];
      break;
    case TOM :
      return TOM_POS[digit];
      break;
    case HOURS :
      return HOURS_POS[digit];
      break;
  }
}



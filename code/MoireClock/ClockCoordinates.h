//==========================================================================
// Moire Clock - ClockCoordinates.h
//
// Copyright (c) 2024, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#ifndef CLOCKCOORDINATES_H
#define CLOCKCOORDINATES_H


// position in steps for each digit
const long HOURS_POS[13] = {0, -450, -975, -1450, -1950, -2450, -3000, -3500, -4000, -4500, -4975, -5475, }; //{0, -3480, -3940, -4440, -4920, -5440, -20, -550, -1020, -1520, -2020, -2520, -3000};  // 0 - 12 
const long TOM_POS[6] = {0, -30, -60, -95, -125, -160}; //{-6030, -6060, -6090, -6120, -6160, -6190}; // 0 - 5
const long MINUTES_POS[10] = {0, -30, -35, -60, -100, -6005, -6040, -6080, -6120, -6160}; // 0 - 9


long GetDigitSteps(int iTime, int iDigit); 

#endif //CLOCKCOORDINATES_H

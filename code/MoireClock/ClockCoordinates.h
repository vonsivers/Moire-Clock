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
const long HOURS_POS[13] = {0, -3480, -3940, -4440, -4920, -5440, -20, -540, -1020, -1520, -2020, -2520, -3000};  // 0 - 12 
const long TOM_POS[6] = {-5915, -5940, -5980, -6015, -6050, -6090}; // 0 - 5
const long MINUTES_POS[10] = {-11305, -11330, -11340, -11360, -11395, -5360, -5405, -5445, -5490, -5530}; // 0 - 9


long GetDigitSteps(int iTime, int iDigit); 

#endif //CLOCKCOORDINATES_H

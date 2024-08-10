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
const long HOURS_POS[13] = {0, -545, -1050, -1580, -2120, -2660, -3180, -3720, -4250, -4790, -5320, -5870, -6390};  // 0 - 12 
const long TOM_POS[6] = {-2380, -2395, -2415, -2432, -2449, -2467}; // 0 - 5
const long MINUTES_POS[10] = {10, -11, -33, -54, -75, -2442, -2465, -2486, -2508, -2529}; // 0 - 9


long GetDigitSteps(int iTime, int iDigit); 

#endif //CLOCKCOORDINATES_H

//==========================================================================
// Moire Clock -  Clock.h
//
// Copyright (c) 2024, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#ifndef CLOCK_H
#define CLOCK_H

void UpdateDisplayTime();
void UpdateDisplayTimeShow();

void RTCInit();

void PrintCurrentTime();

void initTimeShow();

void testHours();
void testTOM();
void testMins();

#endif //CLOCK_H

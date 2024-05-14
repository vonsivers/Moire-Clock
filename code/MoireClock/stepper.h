//==========================================================================
// Moire Clock - stepper.h
//
// Copyright (c) 2024, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#ifndef STEPPER_H
#define STEPPER_H

const int SECONDS = 3;
const int MINUTES = 2;
const int TOM = 1;
const int HOURS = 0;

// Motor parameters
const int HOURS_STEPS_PER_REVOLUTION = 5960; // full steps
const int TOM_STEPS_PER_REVOLUTION = 5960*2; // half steps
const int MINUTES_STEPS_PER_REVOLUTION = 5960*2; // half steps
const int SECONDS_STEPS_PER_REVOLUTION = 5960*4; // quarter steps
const int HOURS_SPEED = 500;
const int TOM_SPEED = 2000;  
const int TOM_ACCELERATION = 100;
const int MINUTES_SPEED = 2000;  
const int MINUTES_ACCELERATION = 100;
const int HOME_SPEED = 500;

// speed of seconds wheel in steps per second
const long SECONDS_SPEED = SECONDS_STEPS_PER_REVOLUTION/360; // /3600; // moire period is 6° so 0.1°/s is one full rotation every 60s

const int directionTowardHome = -1;

void InitSteppers();
void MoveRelative(int iMotor, long lSteps);
void MoveAbsolute(int iMotor, long lSteps);
void MoveAbsoluteCW(int iMotor, long lSteps);
void MoveAbsoluteRevs(int iMotor, float Revs);
long GetCurrentPosition(int iMotor);
void ZeroPosition(int iMotor);
void MoveAllSteppers(long lSECSteps, long lHoursSteps, long lTOMSteps, long lMinutesSteps);
void FindHomePosition();
void TestMotors();
void RotateSeconds();
void AdjustWheel(int iMotor);
void MoveToHome(int iMotor, float speedInStepsPerSecond, long maxDistanceToMoveInSteps, int homeLimitSwitchPin); 
void setSpeed();

#endif //STEPPER_H

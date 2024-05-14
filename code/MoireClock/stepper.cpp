//==========================================================================
// Moire Clock - stepper.cpp
//
// Copyright (c) 2024, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#include <SpeedyStepper.h> // https://github.com/Stan-Reifel/SpeedyStepper
#include "hardware.h"
#include "stepper.h"
#include "LEDs.h"
#include "FastLED.h"

//=====================================
// Global Variables
//=====================================
SpeedyStepper minsStepper; 
SpeedyStepper tomStepper; 
SpeedyStepper hoursStepper; 
SpeedyStepper secStepper; 

int iAcceleration;

//=====================================
// E n a b l e S t e p p e r s
//=====================================
void EnableSteppers() {
    digitalWrite(NOT_ENABLE_PIN, LOW);
}
//=====================================
// D i s a b l e S t e p p e r s
//=====================================
void DisableSteppers() {
    digitalWrite(NOT_ENABLE_PIN, HIGH);
}
//=====================================
// I n i t S t e p p e r s
//=====================================
void InitSteppers() {
    
    InitLEDs(); // also init LEDs

    minsStepper.connectToPins(MINS_STEP_PIN, MINS_DIR_PIN);
    minsStepper.setStepsPerRevolution(MINUTES_STEPS_PER_REVOLUTION);

    tomStepper.connectToPins(TOM_STEP_PIN, TOM_DIR_PIN);
    tomStepper.setStepsPerRevolution(TOM_STEPS_PER_REVOLUTION);

    hoursStepper.connectToPins(HOURS_STEP_PIN, HOURS_DIR_PIN);
    hoursStepper.setStepsPerRevolution(HOURS_STEPS_PER_REVOLUTION);

    secStepper.connectToPins(SEC_STEP_PIN, SEC_DIR_PIN);
    secStepper.setStepsPerRevolution(SECONDS_STEPS_PER_REVOLUTION);

    //Enable
    EnableSteppers();
}

//=====================================
// Set Speed
//=====================================
void setSpeed() {
    
    minsStepper.setSpeedInStepsPerSecond(MINUTES_SPEED);
    minsStepper.setAccelerationInStepsPerSecondPerSecond(MINUTES_ACCELERATION);
    
    tomStepper.setSpeedInStepsPerSecond(TOM_SPEED);
    tomStepper.setAccelerationInStepsPerSecondPerSecond(TOM_ACCELERATION);
    
    hoursStepper.setSpeedInStepsPerSecond(HOURS_SPEED);
    
    secStepper.setSpeedInStepsPerSecond(SECONDS_SPEED);

}
//=====================================
// M o v e R e l a t i v e
//=====================================
void MoveRelative(int iMotor, long lSteps) {

    switch (iMotor) {
      case MINUTES :
          minsStepper.moveRelativeInSteps(lSteps);
          break;
      case TOM :
          tomStepper.moveRelativeInSteps(lSteps);
          break;
      case HOURS :
          hoursStepper.moveRelativeInSteps(lSteps);
          break;
      case SECONDS :
          secStepper.moveRelativeInSteps(lSteps);
          break;
    }

}
//=====================================
// M o v e A b s o l u t e
//=====================================
void MoveAbsolute(int iMotor, long lSteps) {


    switch (iMotor) {
      case MINUTES :
          minsStepper.moveToPositionInSteps(lSteps);
          break;
      case TOM :
          tomStepper.moveToPositionInSteps(lSteps);
          break;
      case HOURS :
          hoursStepper.moveToPositionInSteps(lSteps);
          break;
      case SECONDS :
          secStepper.moveToPositionInSteps(lSteps);
          break;
    }

}

//=====================================
// M o v e A b s o l u t e but always clockwise to eliminate backlash error
//=====================================
void MoveAbsoluteCW(int iMotor, long lSteps) {
  long pos;
  Serial.println("set pos:");
  Serial.println(lSteps);
    switch (iMotor) {
      case MINUTES :
          pos = minsStepper.getCurrentPositionInSteps();
          if(pos-lSteps<0)  { // if move is not clockwise first move to home
            MoveToHome(MINUTES, HOME_SPEED, 1.1*MINUTES_STEPS_PER_REVOLUTION, HALL_MINUTES_PIN);
            //minsStepper.moveToPositionInSteps(-MINUTES_STEPS_PER_REVOLUTION);
            //minsStepper.setCurrentPositionInSteps(0);
          }
          minsStepper.moveToPositionInSteps(lSteps);
          break;
      case TOM :
          pos = tomStepper.getCurrentPositionInSteps();
          if(pos-lSteps<0)  { 
            MoveToHome(TOM, HOME_SPEED, 1.1*TOM_STEPS_PER_REVOLUTION, HALL_TOM_PIN);
            //tomStepper.moveToPositionInSteps(-TOM_STEPS_PER_REVOLUTION);
            //tomStepper.setCurrentPositionInSteps(0);
          }
          tomStepper.moveToPositionInSteps(lSteps);
          break;
      case HOURS :
          pos = hoursStepper.getCurrentPositionInSteps();
          Serial.println("current pos:");
          Serial.println(pos);
          if(pos-lSteps<0)  { 
            Serial.println("move to home");
            MoveToHome(HOURS, HOME_SPEED, 1.1*HOURS_STEPS_PER_REVOLUTION, HALL_HOURS_PIN);
            //hoursStepper.moveToPositionInSteps(-HOURS_STEPS_PER_REVOLUTION);
            //hoursStepper.setCurrentPositionInSteps(0);
          }
          Serial.println("move to set pos");
          hoursStepper.moveToPositionInSteps(lSteps);
          break;
    }

}

//=====================================
// M o v e A b s o l u t e in Revolutions
//=====================================
void MoveAbsoluteRevs(int iMotor, float iRevs) {


    switch (iMotor) {
      case MINUTES :
          minsStepper.moveToPositionInRevolutions(iRevs);
          break;
      case TOM :
          tomStepper.moveToPositionInRevolutions(iRevs);
          break;
      case HOURS :
          hoursStepper.moveToPositionInRevolutions(iRevs);
          break;
      case SECONDS :
          secStepper.moveToPositionInRevolutions(iRevs);
          break;
    }

}
//=====================================
// G e t C u r r e n t P o s i t i o n
//=====================================
long GetCurrentPosition(int iMotor) {
   
   switch (iMotor) {
      case MINUTES :
          return minsStepper.getCurrentPositionInSteps();
          break;
      case TOM :
          return tomStepper.getCurrentPositionInSteps();
          break;
      case HOURS :
          return hoursStepper.getCurrentPositionInSteps();
          break;
      case SECONDS :
          return secStepper.getCurrentPositionInSteps();
          break;
    }  
}
//=====================================
// Z e r o P o s i t i o n
//=====================================
void ZeroPosition(int iMotor) {

    switch (iMotor) {
      case MINUTES :
          minsStepper.setCurrentPositionInSteps(0);
          break;
      case TOM :
          tomStepper.setCurrentPositionInSteps(0);
          break;
      case HOURS :
          hoursStepper.setCurrentPositionInSteps(0);
          break;
      case SECONDS :
          secStepper.setCurrentPositionInSteps(0);
          break;
    }
}
//=====================================
// M o v e A l l S t e p p e r s
//=====================================
void MoveAllSteppers(long lSECSteps, long lHoursSteps, long lTOMSteps, long lMinutesSteps) {


    secStepper.setupMoveInSteps(lSECSteps);
    hoursStepper.setupMoveInSteps(lHoursSteps);
    tomStepper.setupMoveInSteps(lTOMSteps);
    minsStepper.setupMoveInSteps(lMinutesSteps);

    while((!secStepper.motionComplete()) || (!hoursStepper.motionComplete()) || (!tomStepper.motionComplete()) || (!minsStepper.motionComplete()))
    {
        secStepper.processMovement();
        hoursStepper.processMovement();
        tomStepper.processMovement();
        minsStepper.processMovement();
    
    }

}

// move stepper to home
void MoveToHome(int iMotor, float speedInStepsPerSecond, long maxDistanceToMoveInSteps, int homeLimitSwitchPin) {
  //
  // setup the home switch input pin
  //
  pinMode(homeLimitSwitchPin, INPUT_PULLUP);
  delay(1000);    // takes some time to pull pin high

    switch (iMotor) {
      case MINUTES :
          minsStepper.setSpeedInStepsPerSecond(speedInStepsPerSecond);
          // if the home switch is already set, first rotate 90deg than move to home
          if (digitalRead(homeLimitSwitchPin) == LOW) {
            minsStepper.moveRelativeInSteps(MINUTES_STEPS_PER_REVOLUTION/4 * directionTowardHome);
          } 
          minsStepper.setupRelativeMoveInSteps(maxDistanceToMoveInSteps * directionTowardHome);
          while(!minsStepper.processMovement())
          {
            if (digitalRead(homeLimitSwitchPin) == LOW)
            {
              break;
            }
          }
          // Now at home position so set zero
          minsStepper.setCurrentPositionInSteps(0);
          break;
      case TOM :
          tomStepper.setSpeedInStepsPerSecond(speedInStepsPerSecond);
          if (digitalRead(homeLimitSwitchPin) == LOW) {
            tomStepper.moveRelativeInSteps(TOM_STEPS_PER_REVOLUTION/4 * directionTowardHome);
          } 
          tomStepper.setupRelativeMoveInSteps(maxDistanceToMoveInSteps * directionTowardHome);
          while(!tomStepper.processMovement())
          {
            if (digitalRead(homeLimitSwitchPin) == LOW)
            {
              break;
            }
          }
          tomStepper.setCurrentPositionInSteps(0);
          break;
      case HOURS :
          hoursStepper.setSpeedInStepsPerSecond(speedInStepsPerSecond);
          if (digitalRead(homeLimitSwitchPin) == LOW) {
            hoursStepper.moveRelativeInSteps(HOURS_STEPS_PER_REVOLUTION/4 * directionTowardHome);
          } 
          hoursStepper.setupRelativeMoveInSteps(maxDistanceToMoveInSteps * directionTowardHome);
          while(!hoursStepper.processMovement())
          {
            if (digitalRead(homeLimitSwitchPin) == LOW)
            {
              break;
            }
          }
          hoursStepper.setCurrentPositionInSteps(0);
          break;
      }    
    
    
}

//===============================================================================
// F i n d H o m e P o s i t i o n
//===============================================================================
void FindHomePosition() {

    // rotate until hall switch triggers
    
    MoveToHome(MINUTES, HOME_SPEED, 1.1*MINUTES_STEPS_PER_REVOLUTION, HALL_MINUTES_PIN);
    //MoveToHome(TOM, HOME_SPEED, 1.1*TOM_STEPS_PER_REVOLUTION, HALL_TOM_PIN);   
    //MoveToHome(HOURS, HOME_SPEED, 1.1*HOURS_STEPS_PER_REVOLUTION, HALL_HOURS_PIN); 

   
}


// totate motor 10x for manual centering of the axis
void AdjustWheel(int iMotor) {

  switch (iMotor) {
      case MINUTES :
          minsStepper.setSpeedInStepsPerSecond(MINUTES_SPEED/2);
          break;
      case TOM :
          tomStepper.setSpeedInStepsPerSecond(TOM_SPEED/2);
          break;
      case HOURS :
          hoursStepper.setSpeedInStepsPerSecond(HOURS_SPEED/2);
          break;
      case SECONDS :
          secStepper.setSpeedInStepsPerSecond(SECONDS_SPEED*10);
          break;
    }
  MoveAbsoluteRevs(iMotor, -10);

}

// rotate seconds wheel
void RotateSeconds() {
  
  cycleAllLEDs();
  EVERY_N_MILLISECONDS( 1000/SECONDS_SPEED ) { secStepper.moveRelativeInSteps(-1); }

}






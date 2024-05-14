//==========================================================================
// Moire Clock - MoireClock.ino
//
// Copyright (c) 2024, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#include "hardware.h"
#include "stepper.h"
#include "ClockCoordinates.h"     
#include "Clock.h"

//=======================================
// C o n s t a n t s
//=======================================
#define UP_ARROW  0x75 // 'u'
#define DOWN_ARROW 0x64 // 'd'
#define EQUALS_SIGN 0x3D
#define PLUS_SIGN 0x2B
#define MINUS_SIGN 0x2D
#define CTRL_C  0x78 //'x'
#define H_SIGN 0x68 // 'h'
#define T_SIGN 0x74 // 't'
#define M_SIGN 0x6D // 'm'
#define S_SIGN 0x73 // 's'


typedef struct {
  int minutes;
  int tensOfMinutes;
  int hours;
  int seconds;
}myDateTime;

//=======================================
// Global Variables
//=======================================
int iCurrentMotor;


//========================================
// K e y p a d C o n t r o l
//========================================
void KeypadControl() {
  bool bLoop;
  bool bArrowSequence;
  int in;
  long lSteps;


  // initialize variables
  bLoop = true;
  //bArrowSequence = false;
  lSteps = 1;
  iCurrentMotor = MINUTES;

  while (bLoop) {  
 
    if(Serial.available()){
      in = Serial.read();



      switch (in) {
        case CTRL_C:      //'x'
            bLoop=false;
            return;
            break;
        case DOWN_ARROW:
              Serial.print(F("DOWN\n"));
              MoveRelative(iCurrentMotor,lSteps);
            break;
        case UP_ARROW:
              Serial.print(F("UP\n"));
              MoveRelative(iCurrentMotor, -lSteps);
            break;
        case PLUS_SIGN:
        case EQUALS_SIGN:   //plus (or equals)
            Serial.print(F("Increase Steps\n"));
             lSteps = lSteps+100;
            break;
        case MINUS_SIGN:        // minus
            Serial.print(F("Decrease Steps\n"));
             lSteps = lSteps-100;
            break;
        case 0x7A:      // 'z'
            ZeroPosition(iCurrentMotor);
            break;
        case M_SIGN:
          iCurrentMotor = MINUTES;
          break;
        case T_SIGN:
          iCurrentMotor = TOM;
          break;
        case H_SIGN:
          iCurrentMotor = HOURS;
          break;
        case S_SIGN:
          iCurrentMotor = SECONDS;
          break;
        case '1':
          lSteps = 1;
          break;
        case '2':
          lSteps = 5;
          break;
        case '3':
          lSteps = 10;
          break;
        case '4':
          lSteps = 20;
          break;
        case '5':
          lSteps = 50;
          break;
        case '6':
          lSteps = 100;
          break;
       case '7':
          lSteps = 200;
          break;
       case '8':
          lSteps = 800;
          break;
       case '9':
          lSteps = 1000;
          break;
       default:
          Serial.print(F("Input detected: '"));
          Serial.print(in);
          Serial.print(F("' 0x"));
          Serial.print(in, HEX);
          Serial.print("\n");
          break;
     }  //switch  

    //show current values
    Serial.print("Current Position: ");
    Serial.println(GetCurrentPosition(iCurrentMotor));

    Serial.print("Steps: ");
    Serial.print(lSteps);
    Serial.print("\n");
     
    } // if
  } // while

}
//=======================================
// R u n C l o c k
//=======================================
void RunClock() {

  while(1) {
    UpdateDisplayTime();
  }
}

//=======================================
// R u n C l o c k in show mode
//=======================================
void RunClockShow() {

  initTimeShow();
  
  while(1) {
    UpdateDisplayTimeShow();
  }
}
//-------------------------------------
// s e t u p
//-------------------------------------
void setup()
{
    Serial.begin(9600);
    Serial.print("Moire Clock version 1.0\n");
 
    pinMode(NOT_ENABLE_PIN, OUTPUT);


  RTCInit();
  InitSteppers();
  delay(1000);
  //AdjustWheel(SECONDS);
  FindHomePosition();
  //KeypadControl();  // control motors via serial terminal
  setSpeed(); // speed must be set after homing
  RunClock();
  //RunClockShow();  // run clock in demo mode
}
//-------------------------------------
// l o o p
//
// 
//-------------------------------------
void loop()
{
  //testHours();
  //testTOM();
  //testMins();
  //RotateSeconds();
}

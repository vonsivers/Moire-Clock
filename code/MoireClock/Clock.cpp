//==========================================================================
// Moire Clock -  Clock.cpp
//
// Copyright (c) 2024, Moritz v. Sivers
//
// based on Slide Clock by Craig Colvin, https://github.com/moose408/SlideClock
//
// Licensed under Creative Commons License
// Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
//==========================================================================

#include <Arduino.h>

#include "Clock.h"
#include "ClockCoordinates.h"
#include "RTClib.h" // https://github.com/adafruit/RTClib
#include "hardware.h"
#include "stepper.h"

RTC_DS3231 rtc;
DateTime dtCurrentDisplayedTime;


//=========================================
// I n c r e m e n t T i m e 
//=========================================
int IncrementTime(int iTimeValue, int iMaxValue) {
  int iNewValue;

  iNewValue = iTimeValue + 1;
  if (iNewValue > iMaxValue) {
    iNewValue = 0;
  }

  return (iNewValue);
}
//=========================================
// H a s A M i n u t e P a s s e d
//
// This expects both times to be in 24h
// notation
//=========================================
bool HasAMinutePassed() {
  DateTime dtNow = rtc.now();

  if ((dtNow.unixtime() - dtCurrentDisplayedTime.unixtime()) >= 60) 
    {
    return true;
    }
  else
    {
    return false; 
    }

}

//=========================================
// G e t D i g i t
//
// Returns a single digit out of the DateTime
//=========================================
int GetDigit(DateTime dtTime, int iDigitPos)
{
  switch(iDigitPos) 
  {
    case MINUTES:
      return dtTime.minute() % 10;
      break;
    case TOM:
     return dtTime.minute() / 10;
     break;
    case HOURS:
      if(dtTime.hour()>12) {
        return dtTime.hour() - 12;
      }
      else {
        return dtTime.hour();
      }
      
      break; 
  }
}

//=========================================
// R T C I n i t 
//=========================================
void RTCInit() {
    //------------
    // Setup RTC
    //------------

 if (! rtc.begin()) {
        Serial.println("RTC is NOT running!");
      }

  //Uncommenting this will initialize the clock to the
  //compile time of this code.
  //rtc.adjust(DateTime(__DATE__, __TIME__));

}

//=========================================
// P r i n t T i m e
//=========================================
void PrintCurrentTime() {
    DateTime dtTime;

    dtTime = rtc.now(); 
    
    Serial.print(GetDigit(dtTime,HOURS));
    Serial.print(":");
    Serial.print(GetDigit(dtTime,TOM));
    Serial.print(GetDigit(dtTime,MINUTES));
    Serial.print("\n");
}//=========================================
// P r i n t T i m e
//=========================================
void PrintTime(DateTime dtTime) {

    Serial.print(GetDigit(dtTime,HOURS));
    Serial.print(":");
    Serial.print(GetDigit(dtTime,TOM));
    Serial.print(GetDigit(dtTime,MINUTES));
    Serial.print("\n");
}
//=========================================
// U p d a t e D i s p l a y T i m e
//
// This will get current time and move 
// any digits that have changed 
//=========================================
void UpdateDisplayTime() {
    DateTime dtNow, dtNewDisplayedTime;

    dtNow = rtc.now(); 

    // Check if minute has passed 
    if (! HasAMinutePassed()) {
      RotateSeconds();  // update seconds
      return;
    }

    //Display time 
    dtNewDisplayedTime = dtNow;
    dtCurrentDisplayedTime = dtCurrentDisplayedTime;

    //Just to clarify, at this point we have 2 DateTime variables
    //    dtNewDisplayedTime = current time read from RTC in 24h format
    //dtCurrentDisplayedTime = time that is currently being displayed and is going to be replaced

    Serial.print("\n\nCurrent displayed time: ");
    PrintTime(dtCurrentDisplayedTime);
    Serial.print("New time: ");
    PrintTime(dtNewDisplayedTime);

    // update hours, tom, minutes
    for(int iMotor=0; iMotor<3; ++iMotor) {
      MoveAbsolute(iMotor, GetDigitSteps(iMotor, GetDigit(dtNewDisplayedTime, iMotor)));
    }

    //Update current display time
    dtCurrentDisplayedTime = dtNow;

}

void UpdateDisplayTimeShow() {

    // Check if 6 seconds have passed
    long lastCheck = millis();
    while ((millis()-lastCheck)/1000 < 6) {
      RotateSeconds();  // update seconds
    }

    //Display time 
    Serial.print("\n\nCurrent displayed time: ");
    PrintTime(dtCurrentDisplayedTime);


    // update hours, tom, minutes
    for(int iMotor=0; iMotor<3; ++iMotor) {
      MoveAbsolute(iMotor, GetDigitSteps(iMotor, GetDigit(dtCurrentDisplayedTime, iMotor)));
    }

    //Update current display time
    dtCurrentDisplayedTime = dtCurrentDisplayedTime + TimeSpan(0, 0, 1, 0);


}

void initTimeShow() {
  DateTime dtNow("2022-01-01T11:55:00");
  dtCurrentDisplayedTime = dtNow;
}

void testHours() {
  for(int dig=1; dig<13; dig++) {
    MoveAbsolute(HOURS, GetDigitSteps(HOURS, dig));
    delay(2000);
  }
  
}

void testTOM() {
  for(int dig=0; dig<6; dig++) {
    MoveAbsolute(TOM, GetDigitSteps(TOM, dig));
    delay(2000);
  }
  
}

void testMins() {
  for(int dig=0; dig<10; dig++) {
    MoveAbsolute(MINUTES, GetDigitSteps(MINUTES, dig));
    delay(2000);
  }
  
}



  

/************************************************************************/
/*									*/
/*  RTCCI2CDemo.pde	-- Example Sketch for RTCCI2C			*/
/*									*/
/************************************************************************/
/*  Author:	Michelle Yu						*/
/*  Copyright (c) 2011, Digilent Inc.  	    				*/
/************************************************************************/
/*
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/************************************************************************/
/*  Module Description:							*/
/*									*/
/* This sketch is an example on how to set/get time on a real-time      */
/* clock/calender using the RTCCI2C library.				*/	
/************************************************************************/
/*  Revision History:							*/
/*									*/
/*  11/10/2011(Michelle Yu): Created                                    */
/*									*/
/************************************************************************/
/************************************************************************/
/*  Board Support:							*/
/*									*/
/*  chipKit Uno with Pmod Shield:     Header J2	                	*/
/*   (Note: To use this, download and deploy the Board Variant for      */
/*          chipKIT UNO32 W/Pmod Shield from the Digilent website)      */              
/*  chipKit Max with Network Shield:  Header J7                         */
/*  Cerebot Mx3ck:                    Header J2                         */
/*  Cerebot Mx4ck:                    Header J6                         */
/*  Cerebot Mx7ck:                    Header J8                         */
/*				  	   				*/
/*                                                                      */
/************************************************************************/

#include <RTCCI2C.h>
#include <Wire.h>


RTCCI2C myRTCC;
int year, mon, date, day, hour, minute, sec, ampm = 0;

void setup() {
  Serial.begin(9600);
  myRTCC.begin();
  
  //print the power-fail time-stamp
  Serial.print("Lost Power at: ");
  printTime(RTCC_PWRD);
  Serial.print("Power was back at: ");
  printTime(RTCC_PWRU);
 
  //set the real time clock 
  myRTCC.stopClock();
  myRTCC.setSec(RTCC_RTCC, 0x25);
  myRTCC.setMin(RTCC_RTCC, 0x35);
  myRTCC.setHour(RTCC_RTCC, 0x12, RTCC_PM);
  myRTCC.setDay(RTCC_RTCC, 0x02);
  myRTCC.setDate(RTCC_RTCC, 0x15);
  myRTCC.setMonth(RTCC_RTCC, 0x11);
  myRTCC.setYear(0x11);
  myRTCC.startClock();  
 
  //set alarm 0 
  myRTCC.setSec(RTCC_ALM0, 0x35);
  myRTCC.setMin(RTCC_ALM0, 0x35);
  myRTCC.setHour(RTCC_ALM0, 0x12, RTCC_PM);
  myRTCC.setDay(RTCC_ALM0, 0x02);
  myRTCC.setDate(RTCC_ALM0, 0x15);
  myRTCC.setMonth(RTCC_ALM0, 0x11);
  
  //set alarm 1
  myRTCC.setSec(RTCC_ALM1, 0x45);
  myRTCC.setMin(RTCC_ALM1, 0x35);
  myRTCC.setHour(RTCC_ALM1, 0x12, RTCC_PM);
  myRTCC.setDay(RTCC_ALM1, 0x02);
  myRTCC.setDate(RTCC_ALM1, 0x15);
  myRTCC.setMonth(RTCC_ALM1, 0x11);
 
  //print current time
  Serial.print("Current time is: ");
  printTime(RTCC_RTCC);
  //print alarm 0
  Serial.print("Alarm 0 is set to : ");
  printTime(RTCC_ALM0);
  //print alarm 1
  Serial.print("Alarm 1 is set to : ");
  printTime(RTCC_ALM1);

  //enables alarm 0
  //set configuration bits to RTCC_ALM_POL | RTCC_ALMC2 | RTCC_ALMC1 | RTCC_ALMC0 
  //this will drive the MPF pin high when the alarm triggered
  //it also sets the alarm to be triggered when the alarm matches 
  //Seconds, Minutes, Hour, Day, Date, Month of the RTCC
  myRTCC.enableAlarm(RTCC_ALM0, RTCC_ALM_POL | RTCC_ALMC2 | RTCC_ALMC1 | RTCC_ALMC0);
  //enable alarm 1
  //set configuration bits to RTCC_ALM_POL 
  //this will drive the MPF pin high when the alarm triggered
  //it also sets the alarm to be triggered when the alarm matches 
  //seconds of the RTCC
  myRTCC.enableAlarm(RTCC_ALM1, RTCC_ALM_POL);
  
  //enable back up battery
  myRTCC.enableVbat();
}

void loop() {
 
  //print current time
  Serial.print("Current time is : ");
  printTime(RTCC_RTCC);
 
  //check if alarm 0 is triggered 
  if(myRTCC.checkFlag(RTCC_ALM0))
  {
    //alarm 0 has been triggered
    Serial.println("ALM0!!!");
    //disable alarm 0, alarm 0 will not be triggered anymore
    myRTCC.disableAlarm(RTCC_ALM0);
  }
  
  //check if alarm 1 is triggered 
  if(myRTCC.checkFlag(RTCC_ALM1))
  {
    //alarm 1 has been triggered
    Serial.println("ALM1!!!");
    //turn off alarm 1, alarm 1 will still be triggered on next match
    myRTCC.alarmOff(RTCC_ALM1);
  }
 
  // delay to print every second
  delay(950);
}

void printTime (uint8_t src)
{
   // get all paratmeters of the src
   sec= myRTCC.getSec(src);
   minute= myRTCC.getMin(src);
   hour= myRTCC.getHour(src);
   ampm = myRTCC.getAmPm(src);
   day =  myRTCC.getDay(src);
   date= myRTCC.getDate(src);
   mon= myRTCC.getMonth(src);
   year= myRTCC.getYear(); 
   
  
  // print all parameter of the src 
   Serial.print(mon, HEX);
   Serial.print("/");
   Serial.print(date, HEX);
   //year is only available for the RTCC
   if( src == RTCC_RTCC)
   {
     Serial.print("/");
     Serial.print(year, HEX);
   }
   Serial.print("  day");
   Serial.print(day, HEX);
   Serial.print("  ");
   Serial.print(hour, HEX);
   Serial.print(":");
   Serial.print(minute, HEX);
   
   //second is not supported by the power fail registers
   if( src != RTCC_PWRD && src != RTCC_PWRU)
   {
     Serial.print(":");
     Serial.print(sec, HEX);
   }

   if(ampm)
   {
      Serial.println("  PM");
   }
   else
   {
      Serial.println("  AM");
   }

}


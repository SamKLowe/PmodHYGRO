/************************************************************************/
/*																		*/
/*	HYGRO.cpp	--	Definition for HYGRO library 	    	            */
/*																		*/
/************************************************************************/
/*	Author:		Sam Lowe												*/
/*	Copyright 2016, Digilent Inc.										*/
/************************************************************************/
/*  File Description:													*/
/*		This file defines functions for HYGRO						    */
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	9/29/2016(SamL): created											*/
/*																		*/
/************************************************************************/


/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */
#include "HYGRO.h"

/* ------------------------------------------------------------ */
/*				Procedure Definitions							*/
/* ------------------------------------------------------------ *

/* ------------------------------------------------------------------- */
/** void HYGRO::begin()
**
**	Parameters:
**		None
**
**
**	Return Value:
**		None
**
**
**	Description:
**		This function sets up I2C and calls the init sequence
*/
void HYGRO::begin()
{
	Wire.begin();
	HYGRO_init();
}


/* ------------------------------------------------------------------- */
/** void HYGRO::init()
**
**	Parameters:
**		None
**
**
**	Return Value:
**		None
**
**
**	Description:
**		This function configures the device to only read humidity 
**		or temperature at the highest resolution
*/
void HYGRO::init(void)
{
	write_register(CONFIG, 0x0000);
}

/* ------------------------------------------------------------------- */
/** void HYGRO::get_temp()
**
**	Parameters:
**		None
**
**
**	Return Value:
**		uint16_t temperature 
**
**
**	Description:
**		This function configures the device to only read humidity 
**		or temperature at the highest resolution
*/
uint16_t HYGRO::get_temp(void)
{
	read_register(TEMPERATURE);
	
}
/* ------------------------------------------------------------------- */
/** void HYGRO::get_humidity()
**
**	Parameters:
**		None
**
**
**	Return Value:
**		None
**
**
**	Description:
**		This function configures the device to only read humidity 
**		or temperature at the highest resolution
*/
uint16_t HYGRO::get_humidity(void)
{
	read_register(HUMIDITY);
}
/* ------------------------------------------------------------------- */
/** void HYGRO::write_register()
**
**	Parameters:
**		None
**
**
**	Return Value:
**		None
**
**
**	Description:
**		This function configures the device to only read humidity 
**		or temperature at the highest resolution
*/
void HYGRO::write_register(uint8_t reg_addr, uint16_t data)
{
	 Wire.beginTransmission(0x40);
	 Wire.write(reg_addr);
	 Wire.write(data);
	 Wire.endTransmission();    // stop transmitting
}
/* ------------------------------------------------------------------- */
/** void HYGRO::read_register()
**
**	Parameters:
**		reg_addr: address to read from**
**
**	Return Value:
**		uint16_t value: register value
**
**
**	Description:
**		This function configures the device to only read humidity 
**		or temperature at the highest resolution
*/
uint16_t HYGRO::read_register(uint8_t reg_addr)
{
	uint16_t result = 0;
	Write.beginTransmission(0x40);
	Wire.write(reg_addr);
	Wire.write(0x00);
	Wire.endTransmission();
	
	Wire.requestFrom(0x40, 2);
    while (Wire.available()) { // slave may send less than requested
		result = Wire.read(); // receive a byte
		result = result << 8;
		result = result | Wire.read();
		Serial.println(buf, HEX);         // print the character
    }
	
}


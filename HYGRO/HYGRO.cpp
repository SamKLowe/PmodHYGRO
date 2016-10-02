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
	init();
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
**		This function reads the temperature rating from the Hygrometer
**		returns its value in Celcius 
*/
double HYGRO::get_temp(void)
{	
	double  temp = 0;
	init();
	//Serial.println(read_register(TEMPERATURE), DEC);
	
	
	temp = ((float)((float)read_register(TEMPERATURE)/65536)*165)-40;
	return temp;
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
**		This function reads the humidity rating from the Hygrometer
**		returns its value in percentage 
*/
double HYGRO::get_humidity(void)
{
	double humid = 0;
	init();
	humid = ((float)read_register(HUMIDITY)/65536)*100;
	return humid;
}
/* ------------------------------------------------------------------- */
/** void HYGRO::get_deviceID()
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
uint16_t HYGRO::get_deviceID(void)
{
	return read_register(DEVICE_ID);
}
/* ------------------------------------------------------------------- */
/** void HYGRO::get_manufacturerID()
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
uint16_t HYGRO::get_manufacturerID(void)
{
	return read_register(MANUFACTURER_ID);
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
	uint8_t buf = data >> 8;
	 Wire.beginTransmission(0x40);
	 Wire.write(reg_addr);
	 Wire.write(buf);
	 Wire.write((data & 0x00FF));
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
	Wire.beginTransmission(0x40);
	Wire.write(reg_addr);
	Wire.endTransmission();
	
	delay(10);
	
	Wire.requestFrom(0x40, 2);
    while (Wire.available()) { // slave may send less than requested
		result = Wire.read(); // receive a byte
		result = result << 8;
		result = result | Wire.read();
    }
	
	return result;	
	
}


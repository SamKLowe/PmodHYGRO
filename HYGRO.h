/************************************************************************/
/*																		*/
/*	HYGRO.h	--	Declaration for HYGRO library 	    			*/
/*																		*/
/************************************************************************/
/*	Author:		Samuel Lowe												*/
/*	Copyright 2011, Digilent Inc.										*/
/************************************************************************/
/*  File Description:													*/
/*		This file declares functions for PmodHYGRO	    				*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	9/29/2016(SamL): created											*/
/*																		*/
/************************************************************************/
#if !defined(HYGRO_H)
#define HYGRO_H


/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */

#include <Wire.h>
#include "Arduino.h"

/* ------------------------------------------------------------ */
/*					Register Declarations						*/
/* ------------------------------------------------------------ */

#define HUMIDITY		0x01
#define TEMPERATURE		0x00
#define CONFIG			0x02
#define SERIAL_1		0xFB
#define SERIAL_2		0xFC
#define SERIAL_3		0xFD
#define MANUFACTURER_ID	0xFE //0x5449 
#define DEVICE_ID		0xFF //0x1050

/* ------------------------------------------------------------ */
/*					Procedure Declarations						*/
/* ------------------------------------------------------------ */


class HYGRO {
public:

  //initialize 
  void begin();
  void init();
  
  //get functions
  double get_temp(void);
  double get_humidity(void);
  uint16_t get_deviceID(void);
  uint16_t get_manufacturerID(void);
    
  //register functions
  void write_register(uint8_t reg_addr, uint16_t data);
  uint16_t read_register(uint8_t reg_addr);
  
  
  
};



#endif





#include <Wire.h>
#include "HYGRO.h"

HYGRO my_hygro;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  my_hygro.begin();

//check device ID
  delay(1);
  Serial.print("Device ID: ");Serial.print(my_hygro.get_deviceID());
  if(my_hygro.get_deviceID() == 0x1050)
    Serial.println("  PASS");
  else
    Serial.println("  FAILED");

//check man ID
  delay(1);
  Serial.print("Manufacturer ID: ");Serial.print(my_hygro.get_manufacturerID());
  if(my_hygro.get_manufacturerID() == 0x5449)
    Serial.println("  PASS");
  else
    Serial.println("  FAILED");

  Serial.print("Temp: ");Serial.print(my_hygro.get_temp());Serial.print("  Humidity: ");Serial.println(my_hygro.get_humidity()); 
}

void loop() {

 Serial.print("Temp: ");Serial.print(my_hygro.get_temp());Serial.print("  Humidity: ");Serial.println(my_hygro.get_humidity());

  delay(6000);
}

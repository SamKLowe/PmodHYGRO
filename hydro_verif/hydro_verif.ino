#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
}

void loop() {

    uint16_t buf = 0;
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(0x40);
  Wire.write(0xFF);  
  Wire.endTransmission();    // stop transmitting

  Wire.requestFrom(0x40, 2);
  while (Wire.available()) { // slave may send less than requested
    buf = Wire.read(); // receive a byte
    buf = buf << 8;
    buf = buf | Wire.read();
    Serial.println(buf, HEX);         // print the character
  }


 Serial.println("loop");         // print the character
  

  delay(50);
}

#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); //RX, TX

void setup() {
//  pinMode(9, OUTPUT);
//  digitalWrite(8, HIGH);
  
  Serial.begin(9600);
  Serial.println("Bluetooth ready to go.");

  //Options: 115200, 38400, 9600
  BT.begin(9600);
}

void loop() {
  if (BT.available()) {
    Serial.write(BT.read());
    //Serial.println(char(BT.read()));
  }
  if (Serial.available()) {
    BT.write(Serial.read());
  }
} 

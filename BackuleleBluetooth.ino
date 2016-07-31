#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11);

const int segp[] =  {3, 4, 5, 2};
const int strp[] =  {6, 7, 8, 9};

bool ps[] = {0, 0, 0};
bool str[] = {0, 0, 0, 0};
bool touched = false;
int num = 0;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(segp[i], INPUT);
  }
  
  Serial.begin(9600);
  Serial.println("Ready to go!!!");
  
  BT.begin(9600);
}

void loop() {

  for (int i = 0; i < 4; i++) {
    str[i] = digitalRead(strp[i]);
  }

  touched = digitalRead(segp[3]);

  for (int i = 0; i < 3; i++) {
    ps[i] = digitalRead(segp[i]);
  }
  
  num = BtoD(ps);

//  Serial.print(touched);
//  Serial.print("; num=");
//  Serial.print(num);
//  Serial.print("; str=");
//
//  for (int i = 0; i < 4; i++) {
//    Serial.print(str[i]);
//    Serial.print(",");
//  }
//
//  Serial.println(";");

  if (str[0] || str[1] || str[2] || str[3]) {
    String cmd = "EVENT_";
    cmd += String(num);
    cmd += str[0]?"1":"0";
    cmd += str[1]?"1":"0";
    cmd += str[2]?"1":"0";
    cmd += str[3]?"1":"0";
    cmd += "#";

    Serial.println(cmd);
    BT.print(cmd);
  }

  if (BT.available()) {
    Serial.write(BT.read());
  }

  if (Serial.available()) {
    BT.write(Serial.read());
  }

  //delay(5);
}

int BtoD(bool bol[]) {
  int somme = 0;
  for (int i = 0; i < 3; i++) {
    somme += bol[i] * (1 << (2 - i));
  } return somme;
}

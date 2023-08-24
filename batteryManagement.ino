#include <BQ24195.h>
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>
#include "batteryControl_JFL.h"


//17:15
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(5000);       
  batterySetup();
  PMIC.disableCharge();

  WiFiDrv::pinMode(25, OUTPUT);
  WiFiDrv::pinMode(26, OUTPUT);
  WiFiDrv::pinMode(27, OUTPUT);

  pinMode(1, OUTPUT); 
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 

}

void loop() {

  delay(2000);
  int batP = batteryCheck();
  String batPS = String(batP);
  Serial.println("Battery at " + batPS + "%");

  if (PMIC.isPowerGood()) {
    WiFiDrv::analogWrite(25, 1); //GREEN
    WiFiDrv::analogWrite(26, 0);   //RED
    WiFiDrv::analogWrite(27, 0);   //BLUE
  } else {
    WiFiDrv::analogWrite(25, 0); //GREEN
    WiFiDrv::analogWrite(26, 1);   //RED
    WiFiDrv::analogWrite(27, 0);   //BLUE
  }

  if (batP > 60) {
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(1, HIGH);
  } else if (batP > 50) {
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(1, HIGH);
  } else if (batP > 40) {
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(1, HIGH);
  } else if (batP > 30) {
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);
    digitalWrite(1, HIGH);
  } else if (batP > 20) {
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    digitalWrite(1, HIGH);
  } 

}

#include <sim900.h> //download library from https://github.com/Seeed-Studio/GPRS_SIM900
#include <SoftwareSerial.h> //default library
#include <Wire.h> //default library

#define x A1
#define y A2
#define z A3

int xsample = 0;
int ysample = 0;
int zsample = 0;

#define samples 10
//fourwheller
#define fourwheller-minVal 1100
#define fourwheller-MaxVal 2820
//twowheller
#define twowheller-minVal 700
#define twowheller-MaxVal 1000

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing....");
   pinMode(2, OUTPUT);  
   pinMode(3, OUTPUT);
   pinMode(4, OUTPUT);
  delay(1000);
  Accelerometerinit();
  delay(2000);
  //mySerial.begin(9600);
  delay(2000);
  Serial.println("Initialized Successfully");
  delay(2000);
  Serial.println("System Ready..");
}


void loop()
{
      int value1 = analogRead(x);
      int value2 = analogRead(y);
      int value3 = analogRead(z);
      int xValue = xsample - value1;
      if(xValue<0){
        xValue = -xValue;
      }
      Serial.print(" xValue = ");
      Serial.println(xValue);
      int yValue = ysample - value2;
       if(yValue<0){
        yValue = -yValue;
      }
      Serial.print(" yValue = ");
      Serial.println(yValue);
      int zValue = zsample - value3;
       if(zValue<0){
        zValue = -zValue;
      }
      Serial.print(" zValue = ");
      Serial.println(zValue);
      if ((xValue > 180 && xValue < 240) || (yValue > 150 && yValue < 240) || (zValue > 150 && zValue < 240))
      {
         Serial.println("Checking the major-bike accident");
        digitalWrite(2,HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4,HIGH );
        delay(100);
      }else if((xValue > 120 && xValue < 180) || (yValue > 120 && yValue < 180) || (zValue > 120 && zValue < 180)){
        Serial.println("Checking the minor-bike accident");
        digitalWrite(2,LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        delay(100);
      }
      if((xValue > 200 && xValue < 300) || (yValue > 200 && yValue < 300) || (zValue > 200 && zValue < 300)){
        Serial.println("Checking the major-car accident");
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4,HIGH );
        delay(100);
      }else if((xValue > 150  && xValue < 200) || (yValue > 150 && yValue < 200) || (zValue > 150 && zValue < 200)){
        Serial.println("Checking the minor-car accident");
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(4,LOW);
        delay(100);
      }
       digitalWrite(2, LOW);
       digitalWrite(3, LOW);
       digitalWrite(4, HIGH);
       delay(250);
}

void updateSerial()
{
  delay(100);
  while (Serial.available())
  {
     Serial.write(Serial.read());//Forward what Software Serial received to Serial Port
  }
}

void Accelerometerinit()
{
  for (int i = 0; i < samples; i++)
  {
    xsample += analogRead(x);
    ysample += analogRead(y);
    zsample += analogRead(z);
  }

  xsample /= samples;
  ysample /= samples;
  zsample /= samples;

  Serial.println(xsample);
  Serial.println(ysample);
  Serial.println(zsample);
}

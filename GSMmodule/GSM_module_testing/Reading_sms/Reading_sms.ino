#include <TinyGPS++.h>
#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM900
SoftwareSerial mySerial(7, 8); //SIM900 Tx & Rx is connected to Arduino #7 & #8
// Variable to store text message
String textMessage;
String pnum1 = "+917981866770";
String pnum2 = "+916301977206";
int satify = 0;
#define x A1
#define y A2
#define z A3
// Create a TinyGPS++ object
TinyGPSPlus gps;
//
//// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(2, 3);//tx and rx is 2 and 3
int xsample = 0;
int ysample = 0;
int zsample = 0;

#define samples 10
#define minVal -150
#define MaxVal 150

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  gpsSerial.begin(9600);
  //Begin serial communication with Arduino and SIM900
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000); 
   Accelerometerinit();
  
  mySerial.println("AT"); //Handshaking with SIM900
  updateSerial();
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CNMI=2,2,0,0,0\r"); // Decides how newly arrived SMS messages should be handled
  updateSerial();
  delay(6000);
}

void loop()
{
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
    }
  }
  if (mySerial.available() > 0) {
    textMessage = mySerial.readString();
    Serial.println(textMessage);
    delay(10);
  }
  if (textMessage.indexOf("ON") >= 0) {
    Serial.println("hjhjjhhjhhgh");
      int value1 = analogRead(x);
      int value2 = analogRead(y);
      int value3 = analogRead(z);
      int xValue = xsample - value1;
      int yValue = ysample - value2;
      int zValue = zsample - value3;
      if (xValue < minVal || xValue > MaxVal  || yValue < minVal || yValue > MaxVal  || zValue < minVal || zValue > MaxVal)
      {
        delay(1000);
        Serial.println("Waiting!!!!!!!!!!!!!!!");
        delay(2000);
        Serial.println("Sending SMS");
        SmsSend(pnum1);
        delay(6000);
        SmsSend(pnum2);
        delay(6000);
      }
  }
  if (textMessage.indexOf("OFF") >= 0) {
    Serial.println("Relay set to OFF");
  }
  if (textMessage.indexOf("STATE") >= 0) {
  }
}

void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

void SmsSend(String num1)
{
  mySerial.println("AT+CMGF=1\r"); // Configuring TEXT mode
  updateSerial();
  String number =  "AT+CMGS=\"" + num1 + "\"";
  mySerial.println(number);//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
   mySerial.print("Accidense help me!!!"); //text content
    updateSerial();
    mySerial.write(26);
  if (gps.location.isValid())
  {
    mySerial.println("Vehicle stolen at this location!!!!!!!"); //text content
    updateSerial();
    mySerial.print("http://maps.google.com/maps?&z=15&mrt=yp&t=k&q="); //text content
    updateSerial();
    mySerial.print(gps.location.lat(), 6);
    updateSerial();
    mySerial.print("+");              //28.612953, 77.231545   //28.612953,77.2293563
    updateSerial();
    mySerial.print(gps.location.lng(), 6);
    updateSerial();
    mySerial.write(26);
  }
  else
  {
    mySerial.print("Vehicle stolen , now currently in this location!!!"); //text content
    updateSerial();
    mySerial.write(26);
  }
  satify=1;
  Serial.println("SMS Sent");
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

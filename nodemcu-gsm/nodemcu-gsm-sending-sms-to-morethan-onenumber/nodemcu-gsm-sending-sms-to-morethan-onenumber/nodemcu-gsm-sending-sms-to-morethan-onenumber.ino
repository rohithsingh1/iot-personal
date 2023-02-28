#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

//Create software serial object to communicate with SIM900
SoftwareSerial mySerial(0, 2); //SIM900 Tx & Rx is connected to Arduino #0 & #2

// cell numbers to which you want to send the security alert message
String pnum1 = "+917981866770"; 
String pnum2 = "+918125336020"; 
String IncomingRing;
void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(115200);
  
  //Begin serial communication with Arduino and SIM900
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Handshaking with SIM900
  updateSerial();
  sendsms(pnum2);
  delay(20000);
  mySerial.println("AT"); //Handshaking with SIM900
  updateSerial();
   sendsms(pnum1);
   delay(20000);
   Callno(pnum1);
}

void loop()
{
   updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
     Serial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

void sendsms(String num1)
{
  mySerial.println("AT+CMGF=1\r"); // Configuring TEXT mode AT+CMGF=1\r
  updateSerial();
  String number =  "AT+CMGS=\""+num1+"\"";
  mySerial.println(number);//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("Testing with gsm module "); //text content
  updateSerial();
  mySerial.write(26);
}

void Callno(String num1)
{
  String number =  "ATD+ "+num1+";";
  mySerial.println(number);//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  delay(20000); // wait for 20 seconds...
  mySerial.println("ATH"); //hang up
  updateSerial();
}

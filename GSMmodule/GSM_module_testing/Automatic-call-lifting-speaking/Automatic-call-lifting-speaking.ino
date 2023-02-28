/*
  Automatic Voice machine using Arudino and GSM900
  Created by: Aswinth Raj B
  Coded on: 22-9-2017
  Website: www.circuitdigest.com
*/

#include <sim900.h> //download library from https://github.com/Seeed-Studio/GPRS_SIM900
#include <SoftwareSerial.h> //default library
#include <Wire.h> //default library

int Incomingch;
String data, Fdata;
// cell numbers to which you want to send the security alert message
//String pnum1 = "+917981866770";
//String pnum2 = "+918309741063";
int satify = 0;
int satify11 = 0;

//Connect Tx pin of GSM to 7 of Arduino
//Connect Rx pin of GSM to 8 of Arduino
SoftwareSerial mySerial(7, 8); //TX,RX

void setup() {
  Serial.begin(9600); //Serial monitor works on 9600 baudrate for debugging
  mySerial.begin(9600);
  pinMode(9, OUTPUT); //pin to turn on Voice
  Serial.println("Initializing the GSM init function.....");
  mySerial.println("AT"); //Handshaking with SIM900
  updateSerial();
  Serial.println("Arduino - Automatic Voice Machine");
  //   sendsms(pnum1);
  //   delay(6000);
  //   sendsms(pnum2);
  delay(6000);
}

/*Function to read Incoming data from GSM to Arduino*/
void check_Incoming()
{
  if (mySerial.available()) {
    Incomingch = mySerial.read(); // Listen to it and store in this variable
    Serial.println(Incomingch);
    if (Incomingch == 10 || Incomingch == 13) //If it says space (10) or Newline (13) it means it has completed one word
    {
      Serial.println("enter into inner-2 shell of check_incomming");
      Serial.println(data);  Fdata = data; data = "";

    } //Print the word and clear the variable to start fresh
    else
    {
      Serial.println("enter into inner-3 shell of check_incomming");
      String newchar = String (char(Incomingch)); //convert the char to string by using string objects
      data = data + newchar; // After converting to string, do string concatenation
      Serial.println(data);
    }
  }
}
/*##End of Function##*/
void loop() {

  Serial.println("Record the Message");
  check_Incoming(); //Read what GSM module is saying
  AnsweringCallAutomatically();
}


void AnsweringCallAutomatically()
{
  Serial.println("enter into outer shell of AnsweringCallAutomatically");
  if (Fdata == "RING") //If the GSM module says RING
  {
    Serial.println("enter into inner-1 shell of AnsweringCallAutomatically");
    delay(5000); //wait for 5sec to create 3 ring delay.
    mySerial.write ("ATA\r\n"); //Answer the call
    Serial.println ("Placed Received");  //Used for debugging
    while (Fdata != "OK") //Until call successfully answered
    {
      check_Incoming(); //Read what GSM module is saying
      Serial.println ("Playing Recorded message");  //Used for debugging

      //Play the recorded voice message
      delay(500);
      digitalWrite(9, HIGH); //Go high
      delay(200);     // wait for 200 msec
      digitalWrite(9, LOW); //Go low
    }
  }
}


void updateSerial()
{
  delay(100);
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

//void sendsms(String num1)
//{
//  mySerial.println("AT+CMGF=1\r"); // Configuring TEXT mode AT+CMGF=1\r
//  updateSerial();
//  String number =  "AT+CMGS=\"" + num1 + "\"";
//  mySerial.println(number);//change ZZ with country code and xxxxxxxxxxx with phone number to sms
//  updateSerial();
//  mySerial.print("Testing with gsm module "); //text content
//  updateSerial();
//  mySerial.write(26);
//}

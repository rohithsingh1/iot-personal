#include <SoftwareSerial.h>
#include <Wire.h> //default library

//Create software serial object to communicate with SIM900
SoftwareSerial mySerial(7, 8); //SIM900 Tx & Rx is connected to Arduino #7 & #8
int Incomingch;
String textMessage, data, Fdata;
void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  pinMode(9, OUTPUT); //pin to turn on Voice
  //Begin serial communication with Arduino and SIM900
  mySerial.begin(9600);
  mySerial.println("AT"); //Handshaking with SIM900
  updateSerial();
  Serial.println("Initialized Successfully");
  Serial.println("Initializing...");
}

void check_Incoming()
{
  if (mySerial.available()) {
    Incomingch = mySerial.read(); // Listen to it and store in this variable
    Serial.println(Incomingch);
    if (Incomingch == 10 || Incomingch == 13) //If it says space (10) or Newline (13) it means it has completed one word
    {
      Serial.println(data);  Fdata = data; data = "";

    } //Print the word and clear the variable to start fresh
    else
    {
      String newchar = String (char(Incomingch)); //convert the char to string by using string objects
      data = data + newchar; // After converting to string, do string concatenation
    }
  }
}
void loop()
{
  mySerial.println("ATA"); //pick up
  if (Serial.available() > 0) {
    // read the incoming byte:
    Incomingch = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(Incomingch, DEC);
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

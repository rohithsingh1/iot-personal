#include <TinyGPS++.h>
#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM900
SoftwareSerial mySerial(7, 8); //SIM900 Tx & Rx is connected to Arduino #7 & #8

// Create a TinyGPS++ object
TinyGPSPlus gps;
bool var = false;
// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(2, 3);//tx and rx is 2 and 3
// cell numbers to which you want to send the security alert message
String pnum1 = "+917981866770"; 
String pnum2 = "+919490452990";
String pnum3 = "+918639921192";
String pnum4 = "+918985069068";

void setup()
{
   Serial.println("Initializing..."); 
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  delay(2000);
  //Begin serial communication with Arduino and SIM900
  mySerial.begin(9600);
   Serial.println("Initializing the GSM init function....."); 
 mySerial.println("AT"); //Handshaking with SIM900
  updateSerial();
  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(9600);
  delay(3000);
  Serial.println("System Ready........"); 
}

void loop()
{
   // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0){
     if (gps.encode(gpsSerial.read())){
       displayInfo(); 
     }
  }
  // If 8000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 8000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  } 
}


void updateSerial()
{
  delay(100);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
    if(var == false){
      var = true;
      Serial.println("sendsms if condition");
      sendsms(pnum2);
      delay(20000);
      sendsms(pnum1);
      delay(20000);
      sendsms(pnum3);
      delay(20000);
      sendsms(pnum4);
      delay(20000);      
    }
  }
  else
  {
    Serial.println("Location: Not Available");
  }
  
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.println();
  Serial.println();
  delay(1000);
}

void sendsms(String num1)
{
   mySerial.println("AT+CMGF=1\r"); // Configuring TEXT mode
  updateSerial();
  String number =  "AT+CMGS=\"" + num1 + "\"";
  mySerial.println(number);//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  if (gps.location.isValid())
  {
    mySerial.println("Accident occured Please help me!!!"); //text content
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
    mySerial.print("Accident occured Please help me!!!"); //text content
    updateSerial();
    mySerial.write(26);
  }
  //satify = 1;
  Serial.println("SMS Sent");
  //delay(1000);
}

#include <GSM.h>
#include <SoftwareSerial.h>

GSM gsmAccess(true);
char myNumber[20];
//Create software serial object to communicate with SIM900
SoftwareSerial mySerial(7, 8); //SIM900 Tx & Rx is connected to Arduino #7 & #8
String str;
void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM900
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Handshaking with SIM900
  updateSerial();
  delay(2000);
//  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
//  updateSerial();
//  delay(2000);
//   mySerial.println("AT+CIMI"); //will return the lipo battery state. The second number is the % full (in this case its 93%) and the third number is the actual voltage in mV (in this case, 3.877 V)
//  updateSerial();
//  delay(2000);
//   mySerial.println("AT+CPAS"); //will return the lipo battery state. The second number is the % full (in this case its 93%) and the third number is the actual voltage in mV (in this case, 3.877 V)
//  updateSerial();
//  delay(2000);
//   mySerial.println("AT+CREG"); //will return the lipo battery state. The second number is the % full (in this case its 93%) and the third number is the actual voltage in mV (in this case, 3.877 V)
//  updateSerial();
//  delay(2000);
//  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
//  updateSerial();
//  delay(2000);
//  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
//  updateSerial();
//  delay(2000);
 str = mySerial.println("AT+CNUM");
 updateSerial();
 theGSM3ShieldV1ModemCore.println("AT+CNUM");
  delay(2000);
  mySerial.println("ATI"); //Get the shield name and revision
  updateSerial();
  delay(2000);
  mySerial.println("AT+COPS=?"); //Return the list of operators present in the network
  updateSerial();
  delay(2000);
//  mySerial.println("AT+CBC"); //will return the lipo battery state. The second number is the % full (in this case its 93%) and the third number is the actual voltage in mV (in this case, 3.877 V)
//  updateSerial();
//  delay(2000);
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
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

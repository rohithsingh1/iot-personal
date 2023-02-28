#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define WIFI_SSID "Boys wifi123"
#define WIFI_PASSWORD "geetha@07"
#define FIREBASE_HOST "accident-detection-syste-a1ad8-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "gSt3r7KMfvCeAggbSCCGO0CO0u9KJOPacwogUzrI"
String Emergencycontact1,Emergencycontact2,Emergencycontact3,name1,name2,name3,phone,vtype;
void setup()
{
  Serial.begin(115200);
  delay(2000);
  Serial.println('\n');  
  wifiConnect();
  delay(2000);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(100);
}

void loop()
{  
  delay(1000);
  if(Emergencycontact1.length()<=1 && Emergencycontact2.length()<=1 && Emergencycontact3.length()<=1){
    Serial.print("Emergency-contact-1: ");
  Emergencycontact1 = Firebase.getString("emergency_contact_1");
  Serial.println(Emergencycontact1);
  delay(1000);
  Serial.print("Emergency-contact-2: ");
  Emergencycontact2 = Firebase.getString("emergency_contact_2");
  Serial.println(Emergencycontact2);
  delay(1000);
  Serial.print("Emergency-contact-3: ");
  Emergencycontact3 = Firebase.getString("emergency_contact_3");
  Serial.println(Emergencycontact3);
  delay(1000);
  Serial.print("name1: ");
  name1 = Firebase.getString("name1");
  Serial.println(name1);
  delay(1000);
  Serial.print("name2: ");
  name2 = Firebase.getString("name2");
  Serial.println(name2);
  delay(1000);
  Serial.print("name3: ");
  name3 = Firebase.getString("name3");
  Serial.println(name3);
  delay(1000);
  Serial.print("phone: ");
  phone = Firebase.getString("phone");
  Serial.println(phone);
  delay(1000);
  Serial.print("vtype: ");
  vtype = Firebase.getString("vtype");
  Serial.println(vtype);
  delay(1000);
 if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  }
  Serial.println(Emergencycontact1);
  Serial.println(Emergencycontact2);
  Serial.println(Emergencycontact3);
  
//  Serial.print("pushed: /logs/");
if(WiFi.status() != WL_CONNECTED)
{
  wifiConnect();
}
delay(1000);
}

void wifiConnect()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);             // Connect to the network
  Serial.print("Connecting to ");
  delay(500);
  Serial.print(WIFI_SSID); 
  Serial.println(" ...");
  int teller = 0;
  while (WiFi.status() != WL_CONNECTED)
  {                                       // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++teller); Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

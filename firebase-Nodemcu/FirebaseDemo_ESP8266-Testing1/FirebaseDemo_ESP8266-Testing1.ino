#include <ESP8266WiFi.h>
//#include <FirebaseESP8266.h>
#include <FirebaseArduino.h>
//
#define WIFI_SSID "Boys wifi123"
#define WIFI_PASSWORD "geetha@07"
#define FIREBASE_HOST "save-6026b.firebaseio.com"
#define FIREBASE_AUTH "YkLbwZCErCjHIhLRCgsiYfw8wfao5eDtVJUI9Iwl"

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
  Serial.print("value: ");
  Serial.println(Firebase.getInt("value"));
  int val = Firebase.getInt("value");
  Serial.println(val);
    digitalWrite(5,val);
  delay(1000);
 //Firebase.setInt("value", 1);
 if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  Serial.print("pushed: /logs/");
 //Firebase.setString("value","1"); 
//Serial.print(Firebase.getString("LED1") + "\n");
//////analogWrite(LED1, Firebase.getString("LED1").toInt());
//////delay(10);
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

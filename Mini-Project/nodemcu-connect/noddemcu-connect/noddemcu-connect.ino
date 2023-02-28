#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

#define input1 16
#define input2 5
#define input3 4

TinyGPSPlus gps;  // The TinyGPS++ object
SoftwareSerial ss(0, 2); // The serial connection to the GPS device

const char* ssid = "Boys wifi123";
const char* password = "geetha@07";
float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;
int intp1,intp2,intp3;
void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  pinMode(input1 , INPUT);
  pinMode(input2 , INPUT);
  pinMode(input3 , INPUT);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  delay(1000);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  delay(5000);
  Serial.println(WiFi.localIP());
  delay(6000);
}

void loop() {
  while (ss.available() > 0){
    if (gps.encode(ss.read()))
    {
       displayInfo();
    }
  }
  if (millis() > 28000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    //while(true);
  }
  Serial.println("Read digital input: ");
  intp1 = digitalRead(input1);
  intp2 = digitalRead(input2);
  intp3 = digitalRead(input3);
  if(intp1==0 && intp2==0 && intp3==0){
    Serial.println("bike met with an minor-accident");
  }
  if(intp1==0 && intp2==1 && intp3==0){
    Serial.println("car met with an minor-accident");
  }
  if(intp1==1 && intp2==0 && intp3==1){
    Serial.println("Bike met with an major-accident");
  }
  if(intp1==1 && intp2==1 && intp3==1){
    Serial.println("car met with an major-accident");
  }
  if(intp1==0 && intp2==0 && intp3==1){
    Serial.println("NO Accident Occured!!!!");
  }
}

void displayInfo(){
  if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        Serial.println(lat_str);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
         Serial.println(lng_str);
      }else{
        Serial.println("Location: Not Available");
      }

      if (gps.date.isValid())
      {
        date_str = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();

        if (date < 10)
          date_str = '0';
        date_str += String(date);

        date_str += " / ";

        if (month < 10)
          date_str += '0';
        date_str += String(month);

        date_str += " / ";

        if (year < 10)
          date_str += '0';
        date_str += String(year);
        Serial.println(date_str);
      }else{
        Serial.println("Date: Not Available");
      }

      if (gps.time.isValid())
      {
        time_str = "";
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();

        minute = (minute + 30);
        if (minute > 59)
        {
          minute = minute - 60;
          hour = hour + 1;
        }
        hour = (hour + 5) ;
        if (hour > 23)
          hour = hour - 24;

        if (hour >= 12)
          pm = 1;
        else
          pm = 0;

        hour = hour % 12;

        if (hour < 10)
          time_str = '0';
        time_str += String(hour);

        time_str += " : ";

        if (minute < 10)
          time_str += '0';
        time_str += String(minute);

        time_str += " : ";

        if (second < 10)
          time_str += '0';
        time_str += String(second);

        if (pm == 1)
          time_str += " PM ";
        else
          time_str += " AM ";
       Serial.println(time_str);
      }else{
        Serial.println("Time: Not Available");
      }
       Serial.println();
       Serial.println();
       delay(100);
}

#define trigPin1 3
#define echoPin1 2
#define trigPin2 4
#define echoPin2 5
#define buzzerpin 7
#define vibrationmotorpin 6
long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor,vibrationmotorvalue;

void setup()
{
Serial.begin (9600);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(buzzerpin,OUTPUT);
pinMode(vibrationmotorpin,OUTPUT);
vibrationmotorvalue = 0;
}

void loop() {
SonarSensor(trigPin1, echoPin1);
RightSensor = distance;
SonarSensor(trigPin2, echoPin2);
LeftSensor = distance;
Serial.print("front-ultrasconic-sensor  =  ");
Serial.println(LeftSensor);
Serial.print("right-ultrasconic-sensor  =  ");
Serial.println(RightSensor);
if(RightSensor <= 78 || LeftSensor <= 78){
    Serial.println(" obstacle detected");
    vibrationmotorvalue = 200;
    ActivateBuzzer();
  }else{
    noTone(buzzerpin);
    vibrationmotorvalue = 0;
    analogWrite(vibrationmotorpin, vibrationmotorvalue);
  }
}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
}

void ActivateBuzzer(){
 tone(buzzerpin,250);
delay(100);
noTone(buzzerpin);
analogWrite(vibrationmotorpin, vibrationmotorvalue);
 //delay(100);
}

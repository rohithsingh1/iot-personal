int mvm = 6; // micro vibration motor is connected with pin number 5 which is the pwm pin. 
int i;
void setup() {
  Serial.begin (9600);
   pinMode(mvm, OUTPUT);
}

void loop() {
  i = 50;
  // put your main code here, to run repeatedly:
  for(i=50;i<=500;i=i+10){
   analogWrite(mvm, i);
   Serial.print(" Vibration motor frequency : ");
   Serial.println(i);
   delay(1000);
  }
  delay(2000);
}

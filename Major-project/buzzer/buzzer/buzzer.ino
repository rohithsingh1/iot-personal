//Buzzer with tone().
long int i;
void setup() {
Serial.begin (9600);
pinMode(7,OUTPUT);
}

void loop() {
  i = 200;
  for(i = 200;i<=800;i=i+50){
    tone(7,i);  //Syntax : tone(pin_number, frequency)
    delay(100);
    Serial.print("tone value");
    Serial.println(i);
    noTone(7);
    //delay(500);  //Syntax : noTone(pin_number) 
  }
}

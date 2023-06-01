void setup(){
  pinMode(3, INPUT);
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop(){
  Serial.println(digitalRead(3));
  if (digitalRead(8) == 1) {
    digitalWrite(7,HIGH);
    analogWrite(5,150);
    digitalWrite(4,HIGH);
    analogWrite(6,150);
    delay(1000);

  } else {
    analogWrite(5,0);
    analogWrite(6,0);

  }
  if (digitalRead(3) == 0) {
    digitalWrite(7,LOW);
    analogWrite(5,150);
    digitalWrite(4,LOW);
    analogWrite(6,150);
    delay(1000);

  }

}

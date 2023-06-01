void goAhead() {
  analogWrite(5,150);
  digitalWrite(7,HIGH);
  analogWrite(6,150);
  digitalWrite(4,HIGH);
}

void Left() {
  analogWrite(5,0);
  digitalWrite(7,HIGH);
  analogWrite(6,150);
  digitalWrite(4,HIGH);
}

void Stop() {
  analogWrite(5,0);
  digitalWrite(7,HIGH);
  analogWrite(6,0);
  digitalWrite(4,HIGH);
}

void goBack() {
  analogWrite(5,150);
  digitalWrite(7,LOW);
  analogWrite(6,150);
  digitalWrite(4,LOW);
}

void Right() {
  analogWrite(5,150);
  digitalWrite(7,HIGH);
  analogWrite(6,0);
  digitalWrite(4,HIGH);
}

void setup(){
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  Stop();
  pinMode(2, INPUT);
  pinMode(11, OUTPUT);
  pinMode(3, INPUT);
  pinMode(12, OUTPUT);
  pinMode(8, INPUT);
  pinMode(13, OUTPUT);
}

void loop(){
  if (!digitalRead(2)) {
    digitalWrite(11,HIGH);
    Stop();
    delay(2000);

  } else if (!digitalRead(3)) {
    digitalWrite(12,HIGH);
    digitalWrite(11,LOW);
    Stop();
    delay(2000);
  } else if (!digitalRead(8)) {
    Stop();
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
    delay(3000);
  } else {
    goAhead();
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);

  }

}

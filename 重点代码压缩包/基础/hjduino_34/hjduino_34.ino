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

void stop() {
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
  pinMode(2, INPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(3, INPUT);
  pinMode(12, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
}

void loop(){
  if (digitalRead(2)) {
    goAhead();
    digitalWrite(11,HIGH);
    digitalWrite(13,LOW);

  } else if (digitalRead(3)) {
    goBack();
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
  } else if (digitalRead(8)) {
    Left();
  } else if (digitalRead(9)) {
    Right();
  } else {
    stop();
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);

  }

}

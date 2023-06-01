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
  pinMode(9, INPUT);
  pinMode(10, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(11, OUTPUT);
}

void loop(){
  if (!digitalRead(9)) {
    goAhead();
    tone(10,659);
    delay(500);
    tone(10,532);
    delay(200);

  } else if (!digitalRead(A3)) {
    Stop();
    digitalWrite(11,HIGH);
    tone(10,659);
    delay(500);
    pinMode(A0, OUTPUT);
    tone(A0,532);
    delay(200);
  } else {
    noTone(10);
    digitalWrite(11,LOW);
    goAhead();

  }

}

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
  pinMode(A2, INPUT);
  pinMode(11, OUTPUT);
  pinMode(3, INPUT);
}

void loop(){
  if (!digitalRead(A2)) {
    digitalWrite(11,HIGH);
    goBack();
    delay(1000);
    digitalWrite(11,LOW);
    Left();
    delay(1000);
    //Stop();

  } else if (digitalRead(3)) {
    Stop();
  } else {
    goAhead();

  }

}

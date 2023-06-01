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
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop(){
  Serial.println(analogRead(A0));
  if (analogRead(A0) > 800) {
    digitalWrite(11,HIGH);
    digitalWrite(13,LOW);

  } else if (analogRead(A0) > 720) {
    digitalWrite(13,HIGH);
    digitalWrite(11,LOW);
  } else {
    digitalWrite(11,LOW);
    digitalWrite(13,LOW);

  }

}

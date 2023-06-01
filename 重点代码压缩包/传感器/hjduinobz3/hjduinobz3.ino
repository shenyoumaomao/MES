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

float checkdistance_A2_A3() {
  digitalWrite(A2, LOW);
  delayMicroseconds(2);
  digitalWrite(A2, HIGH);
  delayMicroseconds(10);
  digitalWrite(A2, LOW);
  float distance = pulseIn(A3, HIGH) / 58.00;
  delay(10);
  return distance;
}

void setup(){
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);
}

void loop(){
  Serial.println(checkdistance_A2_A3());
  if (checkdistance_A2_A3() > 20) {
    goAhead();

  }
  if (checkdistance_A2_A3() < 20) {
    goBack();
    delay(1000);
    Left();
    delay(500);

  }

}

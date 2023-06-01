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
  pinMode(A2, OUTPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);
}

void loop(){
  Serial.println(checkdistance_A2_A3());

}

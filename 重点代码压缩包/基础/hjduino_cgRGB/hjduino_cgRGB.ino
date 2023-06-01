//声控七彩灯实验
void setup(){
  pinMode(3, INPUT);
  Serial.begin(9600);
  pinMode(11, OUTPUT);
}

void loop(){
  Serial.println(digitalRead(3));
  if (digitalRead(3) == 0) {
    digitalWrite(11,HIGH);
    delay(1000);

  } else {
    digitalWrite(11,LOW);

  }

}

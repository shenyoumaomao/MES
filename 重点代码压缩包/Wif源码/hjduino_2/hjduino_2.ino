volatile int i;

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
  i = 0;
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop(){
  if (Serial.available() > 0) {
    i = Serial.read();
    switch (i) {
     case 01:
      goAhead();
      digitalWrite(11,HIGH);
      break;
     case 02:
      goBack();
      digitalWrite(12,HIGH);
      break;
     case 03:
      digitalWrite(13,HIGH);
      Left();
      break;
     case 04:
      Right();
      break;
     case 00:
      stop();
      digitalWrite(11,LOW);
      digitalWrite(12,LOW);
      digitalWrite(13,LOW);
      break;
    }

  }

}

//蓝牙控制小车
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
}

void loop(){
  if (Serial.available() > 0) {
    i = Serial.read();
    switch (i) {
     case 'A':
      goAhead();
      break;
     case 'B':
      goBack();
      break;
     case 'C':
      Left();
      break;
     case 'D':
      Right();
      break;
     case 'E':
      stop();
      break;
    }

  }

}

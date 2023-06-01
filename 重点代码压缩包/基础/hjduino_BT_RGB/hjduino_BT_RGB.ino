//蓝牙控制RS彩灯实验
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
     case '1':
      digitalWrite(11,HIGH);
      break;
     case '2':
      digitalWrite(12,HIGH);
      break;
     case '3':
      digitalWrite(13,HIGH);
      break;
     case '4':
      digitalWrite(11,LOW);
      break;
     case '5':
      digitalWrite(12,LOW);
      break;
     case '6':
      digitalWrite(13,LOW);
      break;
    }

  }

}

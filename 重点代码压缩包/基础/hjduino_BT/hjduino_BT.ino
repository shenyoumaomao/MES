//蓝牙加七彩灯实验
volatile int i;

void setup(){
  Serial.begin(9600);
  i = 0;
  pinMode(11, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop(){
  if (Serial.available() > 0) {
    i = Serial.read();
    switch (i) {
     case 'A':
      digitalWrite(11,HIGH);
      digitalWrite(7,HIGH);
      analogWrite(5,150);
      digitalWrite(4,HIGH);
      analogWrite(6,150);
      break;
     case 'B':
      digitalWrite(12,HIGH);
      digitalWrite(7,LOW);
      analogWrite(5,150);
      digitalWrite(4,LOW);
      analogWrite(6,150);
      break;
     case 'C':
      digitalWrite(7,HIGH);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,150);
      digitalWrite(13,HIGH);
      break;
     case 'D':
      digitalWrite(7,HIGH);
      analogWrite(5,150);
      digitalWrite(4,HIGH);
      analogWrite(6,0);
      digitalWrite(11,HIGH);
      digitalWrite(12,HIGH);
      break;
     case 'E':
      digitalWrite(11,LOW);
      digitalWrite(12,LOW);
      digitalWrite(13,LOW);
      analogWrite(5,0);
      analogWrite(6,0);
      break;
    }

  }

}

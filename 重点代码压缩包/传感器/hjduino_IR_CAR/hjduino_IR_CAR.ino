#include <IRremote.h>

long ir_item;

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

IRrecv irrecv_2(2);
decode_results results_2;

void setup(){
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  irrecv_2.enableIRIn();
}

void loop(){
  if (irrecv_2.decode(&results_2)) {
    ir_item=results_2.value;
    String type="UNKNOWN";
    String typelist[14]={"UNKNOWN", "NEC", "SONY", "RC5", "RC6", "DISH", "SHARP", "PANASONIC", "JVC", "SANYO", "MITSUBISHI", "SAMSUNG", "LG", "WHYNTER"};
    if(results_2.decode_type>=1&&results_2.decode_type<=13){
      type=typelist[results_2.decode_type];
    }
    Serial.print("IR TYPE:"+type+"  ");
    Serial.println(ir_item,HEX);
    irrecv_2.resume();
  } else {
    if (ir_item == 0XFF18E7) {
      goAhead();

    } else if (ir_item == 0XFF4AB5) {
      goBack();
    } else if (ir_item == 0XFF10EF) {
      Left();
    } else if (ir_item == 0XFF5AA5) {
      Right();
    } else if (ir_item == 0XFF38C7) {
      Stop();
    } else if (ir_item == 0XFF30CF) {
      digitalWrite(11,HIGH);
    } else if (ir_item == 0XFF7A85) {
      digitalWrite(11,LOW);
    }
  }

}

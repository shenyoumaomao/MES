#include <IRremote.h>

long ir_item;

IRrecv irrecv_2(2);
decode_results results_2;

void setup(){
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
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
    if (ir_item == 0xFF30CF) {
      digitalWrite(11,HIGH);
      delay(300);
      digitalWrite(11,LOW);

    }
    if (ir_item == 0xFF18E7) {
      digitalWrite(12,HIGH);
      delay(300);
      digitalWrite(12,LOW);

    }
    if (ir_item == 0xFF7A85) {
      digitalWrite(13,HIGH);
      delay(300);
      digitalWrite(13,LOW);

    }
  }

}

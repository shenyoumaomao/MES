#include <IRremote.h>

long ir_item;

IRrecv irrecv_2(2);
decode_results results_2;

void setup(){
  Serial.begin(9600);
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
  }

}

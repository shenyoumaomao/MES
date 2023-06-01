#include <Servo.h>

Servo servo_9;

void setup(){
  servo_9.attach(9);
}

void loop(){
  servo_9.write(10);
  delay(1000);
  servo_9.write(90);
  delay(1000);
  servo_9.write(170);
  delay(1000);

}

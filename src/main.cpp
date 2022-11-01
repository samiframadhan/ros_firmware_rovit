#include <Arduino.h>
#include "Motor.h"

Motor motor_kiri;
Motor motor_kanan;
unsigned int count = 0;

void setup() {
  // put your setup code here, to run once:
  motor_kiri.set_pindir(2);
  motor_kiri.set_pinpwm(25);
  motor_kiri.set_enable(26);
  motor_kanan.set_pindir(15, true);
  motor_kanan.set_pinpwm(13);
  motor_kanan.set_enable(12);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  motor_kiri.set_pwm(count);
  motor_kanan.set_pwm(count);
  Serial.println(count);
  count++;
  delay(100);
  if(count > 240){
    count = 0;
    Serial.println("batas");
  }
}
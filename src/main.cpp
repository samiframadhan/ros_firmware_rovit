#include <Arduino.h>
#include "Motor.h"

Motor motor_kiri;
// Motor motor_kanan;
int count = 200;

static char* TAG = "Debugging";

motor_configs left_motor;
// motor_configs right_motor;

void setup() {
  // put your setup code here, to run once:
  left_motor.pin_direction  = 12;
  left_motor.pin_enable     = 14;
  left_motor.pin_pwm        = 27;
  left_motor.pin_encoder    = 13;
  left_motor.pwm_freq       = 1000;
  left_motor.reversed       = true;
  motor_kiri.config(left_motor);
  // motor_kanan.set_pindir(15, true);
  // motor_kanan.set_pinpwm(13);
  // motor_kanan.set_enable(12);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (size_t i = 0; i < 100; i++)
  {
    ESP_LOGE(TAG, "Encoder: %d", motor_kiri.get_encoder());
    if(i > 50){
      motor_kiri.set_pwm(200 - (i*4));
    } else motor_kiri.set_pwm(i*4);
    delay(500);
  }
  
}
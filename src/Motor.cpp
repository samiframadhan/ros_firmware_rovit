#include "Motor.h"

uint8_t Motor::channel = 0;

static char *TAG = "Motor";

Motor::Motor() : motor_pid(&set_point, &input, &output)
{
    motor_pwm_channel = channel;
    channel++;
}

Motor::~Motor(){
    motor_encoder.detach();
    ledcDetachPin(motorpins[0]);
}

void Motor::config(motor_configs conf){
    motorpins[0] = conf.pin_direction;
    pinMode(motorpins[0], OUTPUT);
    motorpins[0] = conf.pin_encoder;
    pinpwm_attached = true;
    pindir_attached = true;
    freq = conf.pwm_freq;
    motor_pid.SetTunings(conf.K_P, conf.K_I, conf.K_D);
}

void Motor::set_enable(int pin_enable){
    enable_pin = pin_enable;
    pinMode(enable_pin, OUTPUT);
}

void Motor::set_pinpwm(int pinpwm){
    
    motorpins[0] = pinpwm;
    ledcAttachPin(motorpins[0], motor_pwm_channel);
    ledcSetup(motor_pwm_channel, freq, res);
    ledcWrite(motor_pwm_channel, 0);
}

void Motor::set_pindir(int pindir, bool reverse_){
    motorpins[1] = pindir;
    reverse = reverse_;
    pinMode(motorpins[1], OUTPUT);
}

void Motor::set_pin_enc(int pin_enc){
    motor_encoder.attach_single_edge(pin_enc, motorpins[1]);
    enc_active = true;
}


int Motor::set_pwm(int pwm){
    if((motorpins[0] == 0) || (motorpins[1] == 0)){
        ESP_LOGE(TAG, "Pins not yet configured correctly!");
    }

    if(pwm > 0){
        ledcWrite(motor_pwm_channel, absolute(pwm));
        if(reverse){
            digitalWrite(motorpins[1], BACKWARD);
            digitalWrite(enable_pin, 1);
        } else {
            digitalWrite(motorpins[1], FORWARD);
            digitalWrite(enable_pin, 1);
        }
    } else {
        ledcWrite(motor_pwm_channel, absolute(pwm));
        if(reverse){
            digitalWrite(motorpins[1], FORWARD);
            digitalWrite(enable_pin, 1);
        } else {
            digitalWrite(motorpins[1], BACKWARD);
            digitalWrite(enable_pin, 1);
        }
    }
}

int Motor::getpindir(){
    return motorpins[1];
}

int Motor::getpinpwm(){
    return motorpins[0];
}

uint8_t Motor::getpinpwm_channel(){
    return motor_pwm_channel;
}

int64_t Motor::get_encoder(){
    count = motor_encoder.read_and_clear();
    return count;
}

bool Motor::auto_speed(){
    motor_pid.Compute();
    set_pwm(output);
}

int Motor::absolute(int value){
    if(value<0){
        return -value;
    } else {
        return value;
    }
}
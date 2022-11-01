#include <Arduino.h>
#include "Encoder.h"
#include <QuickPID.h>
#define FORWARD 0
#define BACKWARD 1

struct motor_configs {
    int pin_direction;
    int pin_encoder;
    int pwm_freq;
    float K_P, K_I, K_D;
};

class Motor
{
private:
    bool enc_active = false;
    bool pinpwm_attached = false;
    bool pindir_attached = false;
    int64_t count = 0;
    float set_point = 0.0, input = 0.0, output = 0.0;
    int motorpins[2]= {0,0}; //motorpins0: kontrol pwm, motorpins1: kontrol arah
    int enable_pin = 0;
    QuickPID motor_pid;
    
public:
    Encoder motor_encoder;
    static uint8_t channel;
    uint8_t motor_pwm_channel;
    uint32_t freq = 800;
    uint8_t res = 8;
    bool reverse = false;
    // int encoder_pin = 0;
    bool direction = 0; //0 forward, 1 backward
    void set_pins(int (&pins)[2]);
    void set_pins(int pinpwm, int pindir);
    void set_pinpwm(int pinpwm);
    void set_pindir(int pindir, bool reverse_ = false);
    void set_pin_enc(int pin_enc);
    void set_enable(int enable_pin);
    void config(motor_configs);

    int set_pwm(int pwm_val);
    int getpindir();
    int getpinpwm();
    uint8_t getpinpwm_channel();
    int64_t get_encoder();
    int absolute(int value);
    bool auto_speed();

    Motor(/* args */);
    ~Motor();
};

# ESP32 Motor Control Firmware
This repo initially built from platformio project

This repo contains firmware for controlling 2 wheel brushless DC motor using
Brushless Motor Driver in this [link](https://tokopedia.link/pNh5IbSZBub). It is similar to VNH5019 or VNH2SP30/VNH3SP30 though
the only difference is the motor type

In the specified motor driver, it contains a tachometer and a direction pin. Therefore
this firmware use esp32 pulse counter module to count the pulses to offload the computing a bit

# Build the firmware
This firmware is designed through platformio, so you can just clone it
`git clone https://github.com/samiframadhan/ros_firmware_rovit.git`
and open it in your visual studio code
`code ros_firmware_rovit/`
If you have already installed platformio in your vscode, you can then build it
using platformio's button for that

# Disclaimer
This firmware is not yet ready for tests so you need to use it on your own risk

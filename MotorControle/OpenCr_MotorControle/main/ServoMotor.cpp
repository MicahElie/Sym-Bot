#include "ServoMotor.h"

Servo servo;

ServoMotor::ServoMotor(uint8_t pin)
{
    this->pin = pin;
    servo.attach(pin);
#if DEBUG == 1
    if (servo.attached())
        Serial.print("Ready motor : ");
    else
        Serial.print("Not ready motor : ");
    Serial.println(pin);
#endif
};

// servo.write(angle), angle: the value to write to the servo, from 0 to 180
void ServoMotor::go_to(uint8_t pos) { servo.write(pos); };
void ServoMotor::go_to_home() { go_to(this->home); }
// Return : The angle of the servo, from 0 to 180 degrees.
uint8_t ServoMotor::get_position() { return servo.read(); }

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
void ServoMotor::go_to(uint16_t pos) { servo.write(pos); };
void ServoMotor::go_to_degrees(uint16_t pos) { this->go_to(pos); }
void ServoMotor::go_to_home() { this->go_to(this->home); }
void ServoMotor::go_forward() { this->go_to(60); };
void ServoMotor::go_backward() { this->go_to(180); }

// Return : The angle of the servo, from 0 to 180 degrees.
int16_t ServoMotor::get_position() { return servo.read(); }
int16_t ServoMotor::get_home_offset() { return 0; }
void ServoMotor::setHomingOffset(int16_t pos) { ; }

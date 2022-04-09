#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Servo.h>
#include "Motor.h"

// Definition de la classe moteur pour les moteurs SERVO
// Definition of the motor class for SERVO motors
class ServoMotor: public Motor
{
private:
  uint8_t pin;
  uint16_t home = 180; // degrees

public:
  ServoMotor() = delete;
  ServoMotor(uint8_t pin);
  ~ServoMotor() = default;

  void go_to(int16_t pos);
  void go_to_degrees(int16_t pos);
  void go_to_home();
  void go_forward();
  void go_backward();

  int16_t get_position();
  int16_t get_home_offset();
  void setHomingOffset(int16_t pos);
};

#endif

#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Servo.h>

// Definition de la classe moteur pour les moteurs SERVO
// Definition of the motor class for SERVO motors
class ServoMotor
{
private:
  uint8_t pin;
  uint8_t home = 180; // degrees

public:
  ServoMotor(uint8_t pin);

  void go_to(uint8_t pos);
  void go_to_home();
  uint8_t get_position();
};

#endif

#ifndef DYNAMIXMOTOR_H
#define DYNAMIXMOTOR_H

#include <DynamixelWorkbench.h>
#include "Motor.h"

#if defined(__OPENCM904__)
#define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
#define DEVICE_NAME ""
#endif

// Definition de la classe moteur pour les moteurs dynamixel
// Definition of the motor class for dynamixel motors
// https://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_workbench/#opencr-and-opencm-tutorials
// https://emanual.robotis.com/docs/en/dxl/x/xl430-w250/#profile-acceleration108
// https://emanual.robotis.com/docs/en/dxl/x/xm430-w350/#goal-velocity104
// https://github.com/ROBOTIS-GIT/dynamixel-workbench/blob/09e31a8649a7d3b89d76b6bdd2df3407c1622a5c/dynamixel_workbench_toolbox/src/dynamixel_workbench_toolbox/dynamixel_item.cpp
class DynamixMotor: public Motor
{
private:
    const char *log;
    bool cmdSucceeded;

    uint8_t id;
    uint16_t model_number;
    uint16_t baud = 57600;
    uint16_t velocity = 64;

    // uint16_t zero;      // {0, 1648, 0, 1536}
    // uint16_t home;      // {2047, 2048, 1023, 2048}
    // uint16_t max_limit; // {4095, 2672, 1408, 2560}
    // uint16_t step = 32;
    bool reversed;

public:
    DynamixMotor() = delete;
    DynamixMotor(uint8_t id, uint16_t zero, uint16_t home, uint16_t max_limit, bool reverse);
    ~DynamixMotor() = default;

    void go_to(uint16_t pos);
    void go_to_degrees(uint16_t pos);
    void go_to_home();
    void go_forward();
    void go_backward();

    int16_t get_position();
    int16_t get_home_offset();
    void setHomingOffset(int16_t pos);
};

#endif

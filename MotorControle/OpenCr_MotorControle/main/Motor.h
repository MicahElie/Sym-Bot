#ifndef MOTOR_H
#define MOTOR_H

#define DEBUG 0
#define DEBUG_MSG(msg)    // Serial.print(msg)
#define DEBUG_MSG_LN(msg) // Serial.println(msg)

#include <stdint.h>
#include <DynamixelWorkbench.h>

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
class Motor
{
private:
    const char *log;
    bool cmdSucceeded;

    uint8_t id;
    uint16_t model_number;
    uint16_t baud = 57600;
    uint16_t velocity = 64;

    uint16_t zero;      // {0, 1648, 0, 1536}
    uint16_t home;      // {2047, 2048, 1023, 2048}
    uint16_t max_limit; // {4095, 2672, 1408, 2560}
    uint8_t step = 32;
    bool reversed;

public:
    Motor() = delete;
    Motor(uint8_t id, uint16_t zero, uint16_t home, uint8_t max_limit, bool reverse);
    ~Motor() = default;

    uint16_t get_zero() { return zero; }
    uint16_t get_home() { return home; }
    uint16_t get_max_limit() { return max_limit; }
    uint16_t get_step() { return step; }

    void set_zero(uint16_t zero) { this->zero = zero; }
    void set_home(uint16_t home) { this->home = home; }
    void set_max_limit(uint16_t max_limit) { this->max_limit = max_limit; }
    void set_step(uint16_t step) { this->step = step; }

    void go_to(uint16_t pos);
    void go_to_degrees(uint16_t pos);
    void go_to_home();
    void go_forward();
    void go_backward();

    int32_t get_position();
    int32_t get_home_offset();
    void setHomingOffset(int32_t pos);
};

#endif
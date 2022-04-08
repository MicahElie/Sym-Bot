#ifndef MOTOR_H
#define MOTOR_H

#define DEBUG 0
#define DEBUG_MSG(msg)    // Serial.print(msg)
#define DEBUG_MSG_LN(msg) // Serial.println(msg)

#include <stdint.h>

class Motor 
{
    protected:
        uint16_t zero;
        uint16_t home;
        uint16_t max_limit;
        uint16_t step = 16;

    public:
        uint16_t get_zero() { return zero; }
        uint16_t get_home() { return home; }
        uint16_t get_max_limit() { return max_limit; }
        uint16_t get_step() { return step; }

        void set_zero(uint16_t zero) { this->zero = zero; }
        void set_home(uint16_t home) { this->home = home; }
        void set_max_limit(uint16_t max_limit) { this->max_limit = max_limit; }
        void set_step(uint16_t step) { this->step = step; }

        virtual void go_to(int16_t pos)=0;
        virtual void go_to_degrees(int16_t pos)=0;
        virtual void go_to_home()=0;
        virtual void go_forward()=0;
        virtual void go_backward()=0;

        virtual int16_t get_position()=0;
        virtual int16_t get_home_offset()=0;
        virtual void setHomingOffset(int16_t pos)=0;
};


#endif

#include "Motor.h"

DynamixelWorkbench dxl_wb;

Motor::Motor(uint8_t id, uint16_t zero, uint16_t home, uint8_t max_limit, bool reverse)
{
    this->id = id;

    this->zero = zero;
    this->home = home;
    this->max_limit = max_limit;
    this->reversed = reverse;

    cmdSucceeded = dxl_wb.init(DEVICE_NAME, baud);
    cmdSucceeded = dxl_wb.ping((int8_t)id, &model_number, &log);

    if (reverse)
        cmdSucceeded = dxl_wb.setReverseDirection(id, &log);
    else
        cmdSucceeded = dxl_wb.setNormalDirection(id, &log);

    cmdSucceeded = dxl_wb.jointMode(id, velocity, 0, &log);
    cmdSucceeded = dxl_wb.ledOn((uint8_t)id, &log);

    /* Unit	0.229 [rev/min]	Sets velocity of the Profile
       * Unit	1 [msec]	Sets the time span for the Profile
       * Range	0 ~ 32767	‘0’ represents an infinite velocit */
    // cmdSucceeded = dxl_wb.itemWrite(id, "Profile_Velocity", 50, &log);
    /* Unit	214.577 [rev/min2]	Sets acceleration of the Profile
       * Unit	1 [msec]	Sets accelerating time of the Profile
       * Range	0 ~ 32767	‘0’ represents an infinite acceleration */
    // cmdSucceeded = dxl_wb.itemWrite(id, "Profile_Acceleration", 50, &log);

    // A ajouter pour plus de securite
    // cmdSucceeded = dxl_wb.itemWrite(id, "Max_Position_Limit", 4095, &log);
    // cmdSucceeded = dxl_wb.itemWrite(id, "Min_Position_Limit", 0, &log);
}

void Motor::go_to(uint16_t pos)
{
    pos += zero;
    if (pos > max_limit)
        pos = max_limit;
    dxl_wb.goalPosition(id, (int32_t)pos, &log);
};

// 4096/360 = 11,377777777777777777777777777778
void Motor::go_to_degrees(uint16_t pos) { this->go_to(pos*11.3778); }
void Motor::go_to_home() { this->go_to(this->home); }

void Motor::go_forward()
{
    int32_t pos = get_position();
    pos += step;
    go_to(pos);
};

void Motor::go_backward()
{
    int32_t pos = get_position();
    pos -= step;
    go_to(pos);
}
int32_t Motor::get_position()
{
    int32_t data = 0;
    cmdSucceeded = dxl_wb.itemRead(id, "Present_Position", &data, &log);
    return data;
}

int32_t Motor::get_home_offset()
{
    int32_t data = 0;
    cmdSucceeded = dxl_wb.itemRead(id, "Homing_Offset", &data, &log);
    return data;
}

void Motor::setHomingOffset(int32_t pos)
{
    cmdSucceeded = dxl_wb.itemWrite(id, "Homing_Offset", pos, &log);
}
#ifndef TESTJOINDEVICE_H
#define TESTJOINDEVICE_H

#include "Join.h"

class TestJoinDevice : public Join 
{
    public:
        TestJoinDevice(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche);
        void goTo(int WantedPosition);
};
#endif
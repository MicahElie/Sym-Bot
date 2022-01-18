#include "TestJoinDevice.h"

TestJoinDevice::TestJoinDevice(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche) : Join(position, limite, homePosition, LimiteSwitchPinDroit, LimiteSwitchPinGauche) 
{
    
}

void TestJoinDevice::goTo(int WantedPosition)
{
    if (WantedPosition <= limite)
    {
        position = WantedPosition;
    }   
    else
    {
        position = -1;
    }    
}
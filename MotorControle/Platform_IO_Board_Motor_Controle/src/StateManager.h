#include "Join.h"
#include "Utils/Vector.h"
#include "DriveManager.h"
#include "Comm/ControlMessage.h"

#ifndef STATEMANAGER_H
#define STATEMANAGER_H


class StateManager
{
    public:
        StateManager(DriveManager* drivemanager);
        ~StateManager();
        void updateState(ControlMessage* reponse);
        void goTo(int payload[], int payloadsize);
        void callGoToHome();
        void callibrateDrive(int nbrmotorAInitialiser);
    private:

    protected:
        DriveManager* drivemanager;
     
};
#endif
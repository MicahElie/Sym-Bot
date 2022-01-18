#include "Join.h"
#include "Utils/Vector.h"

#ifndef DRIVEMANAGER_H
#define DRIVEMANAGER_H

class DriveManager
{
    public:
        DriveManager();
        ~DriveManager();
        void addJoin(Join* newJoin);
        void deleteJointAt(int index);
        void goToHome();
        void goToPosition(Vector <int> position);
        void setHomePosition(Vector <int> position);
        void calibrateAllJoin();
        void goToPosition(int position[],int size);
    private:
        Vector <Join*> Joins;
};
#endif
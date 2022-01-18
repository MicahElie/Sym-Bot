#ifndef TEST_STATEMANAGER_H
#define TEST_STATEMANAGER_H

#include "abstractTest.h"

class Test_StateManager : public abstractTest
{
    public:
        void test();
        static void test_callibrateDrive();
        static void test_goTo();
        static void test_callGoToHome();
        static void test_updateState();
        

};
#endif
#ifndef TEST_STEPPERJOIN_H
#define TEST_STEPPERJOIN_H

#include "abstractTest.h"

class Test_StepperJoin : public abstractTest 
{
    public:
        void test();
        static void test_Stepper_getPosition();
        static void test_Stepper_getLimite();
        static void test_Stepper_setLimite();
        static void test_Stepper_getHome();
        static void test_Stepper_setHome();
        static void test_Stepper_goTo();
        static void test_Stepper_goTo_avec_le_moteur();
};
#endif
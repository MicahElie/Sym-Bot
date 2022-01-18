#include <unity.h> 
#include "StepperJoin.h"
#include "Test_StepperJoin.h"

void Test_StepperJoin::test()
{
    RUN_TEST(test_Stepper_getPosition);
    RUN_TEST(test_Stepper_getLimite);
    RUN_TEST(test_Stepper_setLimite);
    RUN_TEST(test_Stepper_goTo);
    RUN_TEST(test_Stepper_getHome);
    RUN_TEST(test_Stepper_setHome);
    RUN_TEST(test_Stepper_goTo_avec_le_moteur);
}

void Test_StepperJoin::test_Stepper_getPosition()
{
    StepperJoin stepperjoin(4069,281,42,0,0);
    TEST_ASSERT_EQUAL(4069,stepperjoin.getPosition());
}

void Test_StepperJoin::test_Stepper_getLimite()
{
   StepperJoin stepperjoin(4069,-2801,42,0,0);
    TEST_ASSERT_EQUAL(-2801,stepperjoin.getLimite());
}

void Test_StepperJoin::test_Stepper_setLimite()
{
    StepperJoin stepperjoin(4069,281,42,0,0);
    stepperjoin.setLimite(18881);
    TEST_ASSERT_EQUAL(18881,stepperjoin.getLimite());
}

void Test_StepperJoin::test_Stepper_getHome()
{
    StepperJoin stepperjoin(4069,281,42,0,0);
    TEST_ASSERT_EQUAL(42,stepperjoin.getHome());
}

void Test_StepperJoin::test_Stepper_setHome()
{
    StepperJoin stepperjoin(4069,281,42,0,0);
    stepperjoin.setHome(30);
    TEST_ASSERT_EQUAL(30,stepperjoin.getHome());
}

void Test_StepperJoin::test_Stepper_goTo()
{
    StepperJoin stepperjoin(4069,281,42,0,0);
    stepperjoin.goTo(107);
    TEST_ASSERT_EQUAL(107,stepperjoin.getPosition());

    stepperjoin.goTo(10080);
    TEST_ASSERT_EQUAL(-1,stepperjoin.getPosition());
}

void Test_StepperJoin::test_Stepper_goTo_avec_le_moteur()
{
    //test goTo_avec_le_moteur
    StepperJoin stepperjoin1(69,20476,42,0,0);
    //test pour la position initiale
    stepperjoin1.goTo(0);
    TEST_ASSERT_EQUAL(0,stepperjoin1.getPosition());
    //test pour 1 tour
    stepperjoin1.goTo(4096);
    TEST_ASSERT_EQUAL(4096,stepperjoin1.getPosition());

    //si si j'envoie une valeur suppérieur à la limite défini 1048576
    stepperjoin1.goTo(2475);
    TEST_ASSERT_EQUAL(2475,stepperjoin1.getPosition());

    //retour à 0
    stepperjoin1.goTo(0);
    TEST_ASSERT_EQUAL(0,stepperjoin1.getPosition());

    //test if the goTo works with a value greater than the limit
    //test si le goTo fonctionne avec une valeur suppérieur à la limite
    stepperjoin1.goTo(20489);
    TEST_ASSERT_EQUAL(-1,stepperjoin1.getPosition());
}









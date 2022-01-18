#include <unity.h> 
#include "Test_Join.h"
#include "TestJoinDevice.h"

void Test_Join::test()
{
    RUN_TEST(test_initialisation_getPosition);
    RUN_TEST(test_initialisation_getLimite);
    RUN_TEST(test_initialisation_setLimite);
    RUN_TEST(test_initialisation_goTo);
    RUN_TEST(test_initialisation_getHome);
    RUN_TEST(test_initialisation_setHome);
    //RUN_TEST(test_initialisation_goTo_avec_le_moteur);
}

void Test_Join::test_initialisation_getPosition()
{
    TestJoinDevice testjoin(69,281,42,0,0);
    TEST_ASSERT_EQUAL(69,testjoin.getPosition());
}

void Test_Join::test_initialisation_getLimite()
{
   TestJoinDevice testjoin(69,281,42,0,0);
    TEST_ASSERT_EQUAL(281,testjoin.getLimite());
}

void Test_Join::test_initialisation_setLimite()
{
    TestJoinDevice testjoin(69,281,42,0,0);
    testjoin.setLimite(181);
    TEST_ASSERT_EQUAL(181,testjoin.getLimite());
}

void Test_Join::test_initialisation_getHome()
{
    TestJoinDevice testjoin(69,281,42,0,0);
    TEST_ASSERT_EQUAL(42,testjoin.getHome());
}

void Test_Join::test_initialisation_setHome()
{
    TestJoinDevice testjoin(69,281,42,0,0);
    testjoin.setHome(3);
    TEST_ASSERT_EQUAL(3,testjoin.getHome());
}

void Test_Join::test_initialisation_goTo()
{
    TestJoinDevice testjoin(69,281,42,0,0);
    testjoin.goTo(107);
    TEST_ASSERT_EQUAL(107,testjoin.getPosition());

    testjoin.goTo(1000);
    TEST_ASSERT_EQUAL(-1,testjoin.getPosition());
}

void Test_Join::test_initialisation_goTo_avec_le_moteur()
{
    //test goTo_avec_le_moteur
    TestJoinDevice testjoin1(69,1048576,42,0,0);
    //test pour la position initiale
    testjoin1.goTo(0);
    TEST_ASSERT_EQUAL(0,testjoin1.getPosition());
    //test pour 1 tour
    testjoin1.goTo(4096);
    TEST_ASSERT_EQUAL(4096,testjoin1.getPosition());

    //si si j'envoie une valeur suppérieur à la limite défini 1048576
    testjoin1.goTo(20480);
    TEST_ASSERT_EQUAL(20480,testjoin1.getPosition());

    //retour à 0
    testjoin1.goTo(0);
    TEST_ASSERT_EQUAL(0,testjoin1.getPosition());

    //test if the goTo works with a value greater than the limit
    //test si le goTo fonctionne avec une valeur suppérieur à la limite
    testjoin1.goTo(2048900);
    TEST_ASSERT_EQUAL(-1,testjoin1.getPosition());
}









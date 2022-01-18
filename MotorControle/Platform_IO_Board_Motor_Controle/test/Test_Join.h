#ifndef TEST_JOIN_H
#define TEST_JOIN_H

#include "abstractTest.h"

class Test_Join : public abstractTest 
{
    public:
        void test();
        static void test_initialisation_getPosition();
        static void test_initialisation_getLimite();
        static void test_initialisation_setLimite();
        static void test_initialisation_getHome();
        static void test_initialisation_setHome();
        static void test_initialisation_goTo();
        static void test_initialisation_goTo_avec_le_moteur();
};
#endif
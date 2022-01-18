#include <unity.h>
#include "../test/abstractTest.h"
#include "Comm/SerialComm.h"

#ifndef TESTSERIALCOMM_H
#define TESTSERIALCOMM_H

class test_Serial_Comm : public  abstractTest 
{
    public:
        void test();
        static void testInit();
};

void test_Serial_Comm::testInit()
{
    SerialComm a(&Serial);
}


void test_Serial_Comm::test()
{
    RUN_TEST(testInit);
}

#endif
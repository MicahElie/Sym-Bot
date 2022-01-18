#include "../test/abstractTest.h"
#include "test_ControlMessage.h"
#include "test_Serial_Comm.h"
#include "test_MessageIO.h"

#ifndef TESTCOMM_H
#define TESTCOMM_H

class TestComm : public abstractTest
{
    public:
        void test();
};



 void TestComm::test()
 {
    test_Serial_Comm test_SerialComm;
    testControlMessage test_ControlMessage;
    testMessageIO test_MessageIO;

    test_SerialComm.test();
    test_ControlMessage.test();
    test_MessageIO.test();

 }

 #endif

#ifndef TESTCONTROLMESSAGE_H
#define TESTCONTROLMESSAGE_H

#include <unity.h>
#include "../test/abstractTest.h"
#include "Comm/ControlMessage.h"


class testControlMessage : public  abstractTest 
 {
    public:
        void test();
    private:
        static void isNormalInisialisationOk();
        static void isTypeInisialisationOk();
        static void isBadInisalistionWorking();
};

#endif
    

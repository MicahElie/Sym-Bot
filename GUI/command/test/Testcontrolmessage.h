#ifndef TESTCONTROLMESSAGE_H
#define TESTCONTROLMESSAGE_H


#include "Comm/ControlMessage.h"

class testControlMessage
 {
    public:
        static void testAll();
    private:
        static void isNormalInisialisationOk();
        static void isTypeInisialisationOk();
        static void isBadInisalistionWorking();
};

#endif


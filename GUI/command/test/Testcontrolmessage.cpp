#include <cassert>
#include "Testcontrolmessage.h"


void testControlMessage::isNormalInisialisationOk()
{
    int data[] = {1,2,3};
    int size = 3;
    int type = 1;

    ControlMessage msg(type,size,data);

    assert(1 == msg.getType());
    assert(3 == msg.getPayLoadSize());

    for(int x=0; x < size;x++)
    {
        assert(data[x] == msg.getPayload()[x]);
    }
}

void testControlMessage::isTypeInisialisationOk()
{
    int type = 1;

    ControlMessage msg(type);

    assert(1 == msg.getType());
    assert(0 == msg.getPayLoadSize());
    assert(0 == msg.getPayload());
}

void testControlMessage::isBadInisalistionWorking()
{
    int type = 1;
    int payloadSize = 2;

    ControlMessage msg(type,payloadSize);

    assert(1 == msg.getType());
    assert(0 == msg.getPayLoadSize());
    assert(0 == msg.getPayload());
}

void testControlMessage::testAll()
{
        assert(isNormalInisialisationOk);
        assert(isTypeInisialisationOk);
        assert(isBadInisalistionWorking);
}

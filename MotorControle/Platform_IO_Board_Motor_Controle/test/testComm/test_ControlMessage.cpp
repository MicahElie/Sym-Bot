#include "test_ControlMessage.h"

void testControlMessage::isNormalInisialisationOk()
{
    int data[] = {1,2,3};
    int size = 3;
    int type = 1;
    
    ControlMessage msg(type,size,data);

    TEST_ASSERT_EQUAL(1,msg.getType());
    TEST_ASSERT_EQUAL(3,msg.getPayLoadSize());
    
    for(int x=0; x < size;x++)
    {
        TEST_ASSERT_TRUE(data[x] == msg.getPayload()[x]);
    }
}

void testControlMessage::isTypeInisialisationOk()
{
    int type = 1;
    
    ControlMessage msg(type);

    TEST_ASSERT_EQUAL(1,msg.getType());
    TEST_ASSERT_EQUAL(0,msg.getPayLoadSize());
    TEST_ASSERT_EQUAL(0,msg.getPayload());
}

void testControlMessage::isBadInisalistionWorking()
{
    int type = 1;
    int payloadSize = 2;

    ControlMessage msg(type,payloadSize);

    TEST_ASSERT_EQUAL(1,msg.getType());
    TEST_ASSERT_EQUAL(0,msg.getPayLoadSize());
    TEST_ASSERT_EQUAL(0,msg.getPayload());
}


void testControlMessage::test()
{
        RUN_TEST(isNormalInisialisationOk);
        RUN_TEST(isTypeInisialisationOk);
        RUN_TEST(isBadInisalistionWorking);
}

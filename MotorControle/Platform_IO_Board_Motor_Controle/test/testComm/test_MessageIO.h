#include <unity.h>
#include "../test/abstractTest.h"
#include "Comm/SerialComm.h"
#include "Comm/MessageIO.h"
#include "testCommDevice.h"

#ifndef TEST_MESSAGEIO
#define TEST_MESSAGEIO

class testMessageIO : public abstractTest
{
    public:
        void test();
        static void isSerialDeviceCorrectlyAdded();
        static void isSendCorrectMessageFormat();
        static void isCorrectlyReaddingMessage();
        static void isHandlingDeserialisationError();
};

void testMessageIO::isSerialDeviceCorrectlyAdded()
{
    MessageIO msgIO;
    
    SerialComm* device = new SerialComm(&Serial);
    
    TEST_ASSERT_EQUAL(0,msgIO.getNbrDevice());
    msgIO.addDevice(device);
    TEST_ASSERT_EQUAL(1,msgIO.getNbrDevice());

    CommDevice* dev = msgIO.getDevice(0);

    TEST_ASSERT_TRUE(dev == device);

}


void testMessageIO::isSendCorrectMessageFormat()
{
    MessageIO msgIO;
    TestCommDevice device;
    
    msgIO.addDevice(&device);

    int data[] = {1,2,3,4};

    ControlMessage msg(2,4,data);

    msgIO.sendMessage(0,msg);
    
    StaticJsonDocument<MaxJsonSize> messageSend = device.getLastMessage();

    TEST_ASSERT_TRUE(messageSend["type"] == 2);
    TEST_ASSERT_TRUE(messageSend["PLS"] == 4);
    
    for(int x=0; x < 4;x++)
    {
        TEST_ASSERT_TRUE(messageSend["data"][x].as<int>() == data[x]);    
    }
        
}

void testMessageIO::isCorrectlyReaddingMessage()
{
    MessageIO msgIO;
    TestCommDevice device;
    
    msgIO.addDevice(&device);

    int data[] = {1,2,3,4};

    ControlMessage msg(2,4,data);

    msgIO.sendMessage(0,msg);
    
    ControlMessage* Cmsg = msgIO.readMessage(0);


    TEST_ASSERT_TRUE(msg.getType() == Cmsg->getType());
    TEST_ASSERT_TRUE(msg.getPayLoadSize() == Cmsg->getPayLoadSize());
    
    for(int x=0; x < msg.getPayLoadSize(); x++)
    {
        TEST_ASSERT_TRUE(msg.getPayload()[x] == Cmsg->getPayload()[x]);    
    }
        
}


void testMessageIO::isHandlingDeserialisationError()
{
    MessageIO msgIO;
    TestCommDevice device;
    
    msgIO.addDevice(&device);

    int data[] = {1,2,3,4};

    ControlMessage msg(2,4,data);

    msgIO.sendMessage(0,msg);
    device.failNextDeserialisation();
    ControlMessage* Cmsg = msgIO.readMessage(0);
    
    TEST_ASSERT_EQUAL(NULL, Cmsg);
}


void testMessageIO::test()
{
    RUN_TEST(isSerialDeviceCorrectlyAdded);
    RUN_TEST(isSendCorrectMessageFormat);
    RUN_TEST(isCorrectlyReaddingMessage);
    RUN_TEST(isHandlingDeserialisationError);
}


#endif
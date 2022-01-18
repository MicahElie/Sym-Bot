#include "Comm/CommDevice.h"

#ifndef TESTCOMMDEVICE_H
#define TESTCOMMDEVICE_H

class TestCommDevice : public CommDevice 
{
    public:
        TestCommDevice(bool isMsgAvailable = true, bool deserialiseError = false){msgAvailble = isMsgAvailable; this->deserialiseError = deserialiseError;};
        StaticJsonDocument<MaxJsonSize> ReadJSon();
        void sendJSon(StaticJsonDocument<MaxJsonSize> message){ lastMessageSend = message;};
        bool isMessageAvailable(){ return msgAvailble;};
        StaticJsonDocument<MaxJsonSize> getLastMessage(){return lastMessageSend;};
        void failNextDeserialisation();
    private:
        bool msgAvailble;
        bool deserialiseError;
        StaticJsonDocument<MaxJsonSize> lastMessageSend;
};

void TestCommDevice::failNextDeserialisation()
{
    deserialiseError = true;
}     

StaticJsonDocument<MaxJsonSize> TestCommDevice::ReadJSon()
{
    if(deserialiseError)
    {
        StaticJsonDocument<MaxJsonSize> msg;
        msg["error"] = "deserialisation";
        return msg;
    }
    else
    {
        return lastMessageSend;
    }  
}

#endif
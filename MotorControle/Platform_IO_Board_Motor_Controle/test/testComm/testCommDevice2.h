#include "Comm/CommDevice.h"

#ifndef TESTCOMMDEVICE2_H
#define TESTCOMMDEVICE2_H

class TestCommDevice2 : public CommDevice 
{
    public:
        TestCommDevice2(bool isMsgAvailable = true, bool deserialiseError = false){msgAvailble = isMsgAvailable; this->deserialiseError = deserialiseError;};
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

void TestCommDevice2::failNextDeserialisation()
{
    deserialiseError = true;
}     

StaticJsonDocument<MaxJsonSize> TestCommDevice2::ReadJSon()
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
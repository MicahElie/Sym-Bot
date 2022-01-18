#include "Controlmessage.h"

ControlMessage::~ControlMessage()
{
    if(payload != 0)
        delete[] payload;
}

ControlMessage::ControlMessage(int type, int payloadSize, int* payload)
{
    this->type = type;
    this->payloadSize = payloadSize;

    if(payloadSize != 0 && payload !=0)
    {
        this->payload = new int[payloadSize];
        for(int x=0; x< payloadSize;x++)
        {
            this->payload[x] = payload[x];
        }
    }
    else
    {
        this->payload = 0;
        this->payloadSize = 0;
    }
}

ControlMessagefloatingPoint::~ControlMessagefloatingPoint()
{
    if(payload != 0)
        delete[] payload;
}

ControlMessagefloatingPoint::ControlMessagefloatingPoint(int type, int payloadSize, float* payload)
{
    this->type = type;
    this->payloadSize = payloadSize;

    if(payloadSize != 0 && payload !=0)
    {
        this->payload = new float[payloadSize];
        for(int x=0; x< payloadSize;x++)
        {
            this->payload[x] = payload[x];
        }
    }
    else
    {
        this->payload = 0;
        this->payloadSize = 0;
    }
}

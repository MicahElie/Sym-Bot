#ifndef CONTROLMESSAGE_H
#define CONTROLMESSAGE_H

enum CONTROL_MESSAGE_ID
{
  SET_HOME_MODEL = 4,
  RESET_ENCODER = 5,
  SET_JOIN_POSITION_MODEL = 6,
  SET_CARTESIEN_POSITION = 8,
  GOTO_HOME = 9,
  OPEN_GRIPPER = 10,
  CLOSE_GRIPPER = 11,
  SET_GRIPPER_POSITION_RATE = 26
};


class ControlMessage
{
    public:
        ControlMessage(int type,int payloadSize=0, int* payload=0);
        ~ControlMessage();
        int  getType()          {return type;};
        int  getPayLoadSize()   {return payloadSize;};
        int* getPayload()       {return payload;};

    private:
        int type;
        int payloadSize;
        int* payload;
};

class ControlMessagefloatingPoint
{
    public:
        ControlMessagefloatingPoint(int type,int payloadSize=0, float* payload=0);
        ~ControlMessagefloatingPoint();
        int  getType()          {return type;};
        int  getPayLoadSize()   {return payloadSize;};
        float* getPayload()       {return payload;};

    private:
        int type;
        int payloadSize;
        float* payload;
};



#endif // CONTROLMESSAGE_H

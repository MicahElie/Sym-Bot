class ControlMessage:
    '''This class transforms message sent to the MessageIO object to be correctly read by it
    
    Attributes (most used for this application):
    ---------------
    SET_HOME :          Message type associated with robot having a new home (ah so cute)
    SET_JOIN_POSITION : Message type associated with robot being control with angle sent to joints
    GOTO_HOME :         Message type associated with robot going home (must be confortable)
    SET_JOG :           Message type associated with robot controlled with jogMode (see translate.py)
     '''
    SET_HOME = 3
    SET_HOME_MODEL = 4
    SET_JOIN_POSITION_MODEL = 6
    SET_JOIN_POSITION = 7
    SET_CARTESIAN_POSITION = 8
    GOTO_HOME = 9
    OPEN_GRIPPER = 10
    CLOSE_GRIPPER = 12
    SET_GRIPPER_POSITION = 24
    SET_GRIPPER_POSITION_RATE = 26
    SET_JOG = 77

    def __init__(self, type, payload=[]):
        self.type = type
        self.payload = payload

    def getType(self):
        return self.type

    def getPayloadSize(self):
        return len(self.payload)

    def getPayload(self):
        return self.payload

class ControlMessage:
    '''This class transforms message sent to the MessageIO object to be correctly read by it
    
    Attributes (most used for this application):
    ---------------
    SET_HOME :              Setting new
    SET_JOINT_POSITION :    Message type associated with robot being control with angle sent to joints
    GOTO_HOME :             Message type associated with robot going home (must be confortable)
    SET_JOG :               Message type associated with robot controlled with jogMode (see translate.py)
    '''

    SET_HOME = 3
    SET_HOME_MODEL = 4
    SET_JOINT_POSITION_MODEL = 6
    SET_JOINT_POSITION = 7
    SET_CARTESIAN_POSITION = 8
    GOTO_HOME = 9
    OPEN_GRIPPER = 10
    CLOSE_GRIPPER = 12
    SET_GRIPPER_POSITION = 24
    SET_GRIPPER_POSITION_RATE = 26
    SET_JOG = 77

    # SET VALUE IN[01, 09]
    SET_ZERO_POSITION_INDEX = 1,
    SET_HOME_POSITION_INDEX = 2,
    SET_MAX_POSITION_INDEX = 3,
    # RETURN VALUE IN[11, 19]
    RETURN_ZERO_POSITION_INDEX = 11,
    RETURN_HOME_POSITION_INDEX = 12,
    RETURN_MAX_POSITION_INDEX = 13,
    RETURN_ACTUAL_POSITION_INDEX = 17,
    # ACTION IN[21, 29]
    GO_TO_JOIN_INDEX = 21,
    GO_TO_HOME_INDEX = 22,
    GO_TO_JOG_INDEX = 23,
    ACTION_OPEN_GRIPPER = 25,
    ACTION_CLOSE_GRIPPER = 26,
    ACTION_POSITION_GRIPPER = 27

    def __init__(self, type, payload=[]):
        self.type = type
        self.payload = payload

    def getType(self):
        return self.type

    def getPayloadSize(self):
        return len(self.payload)

    def getPayload(self):
        return self.payload

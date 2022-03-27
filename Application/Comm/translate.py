from enum import Enum
from Comm.ControlMessage import ControlMessage
from Comm import MessageIO

class translate:

    JOG = 0;
    JOINT = 1;
    CART = 2;
    AI = 3;
    INTERFACE = 4;

    lastMsgMotor = [0,0,0,0]
    currentMsgMotor = [0,0,0,0]
    enumRep = 0

    mode = 0
    flexion = [0,0,0,0]
    imu = [0,0,0]

    # Forme du message recu par le gant
    # "Mode: ", "Flex : [4]", "IMU : [3]"

    def __init__(self, msgIO):
        self.msgIO = msgIO
        
    def getMode(self):
        return self.mode

    def getFlex(self, index):
        return self.flexion[index]

    def getImu(self, index):
        return self.imu[index]
    
    def getMsgMotor(self,index):
        return self.currentMsgMotor[index]


    def chooseMode(self,msgGlove):
        '''This function analyses the message from the glove, determines the mode and calls the right translation function

        Parameters,
        -------------
        msgGlove : double[] Data from the glove
        '''

        match msgGlove['Mode']:
            case 1:
                print("this is jog mode")
                self.mode = msgGlove['Mode']
                self.jogMode(msgGlove["Flex"], msgGlove["IMU"])
                
            case 2:
                print("this is joint mode")
                self.mode = msgGlove['Mode']

            case 3:
                print("this is cartesian mode")
                self.mode = msgGlove['Mode']

            case 4:
                print("this is AI mode")
                self.mode = msgGlove['Mode']

            case 5:
                print("this is interface mode")
                self.mode = msgGlove['Mode']


    def jogMode(self, flexion, imu):
        '''This function moves the motors as long as fingers are  in flexion
        
        Parameters
        --------------
        flexion : int Values associated with the four flexing fingers
        imu : double Values associated with the IMU which gives the direction of the hand
        '''
        tresholdFlex = 80
        treshold_IMU_pos = 0.50
        treshold_IMU_neg = -0.50 
        self.currentMsgMotor = [0,0,0,0]
        sumFinger = 0
        griperIncrement = 0

        # Verify the rotation of the hand associated with reversing direction
        if imu[2] <= treshold_IMU_neg:
            # Verify the flexion of the 3 fingers associated to joint 1,2,3
            for id in range(0,3):
                if flexion[id] >= tresholdFlex:
                    self.currentMsgMotor[id] = -1
                    sumFinger += 1

            # Verify the flexion of the last finger associated with the gripper        
            if flexion[3] >= tresholdFlex and sumFinger == 3:
                if griperIncrement  == 0:
                    griperIncrement = 1
                elif griperIncrement == 1:
                    griperIncrement = 0
                self.currentMsgMotor[3] = griperIncrement

        elif imu[2] >= treshold_IMU_pos:  
            # Verify the flexion of the 3 fingers associated to joint 1,2,3
            for id in range(0,3):
                if flexion[id] >= tresholdFlex:
                    self.currentMsgMotor[id] = 1
                    sumFinger += 1

            # Verify the flexion of the last finger associated with the gripper        
            if flexion[3] >= tresholdFlex and sumFinger == 3:
                # griperIncrement = !griperIncrement
                if griperIncrement  == 0:
                    griperIncrement = 1
                elif griperIncrement == 1:
                    griperIncrement = 0
                self.currentMsgMotor[3] = griperIncrement

        else: pass

        if self.currentMsgMotor == self.lastMsgMotor and self.enumRep < 3:
            msg_to_motor = ControlMessage(ControlMessage.SET_JOG, self.lastMsgMotor)
            self.msgIO.sendMessage(0, msg_to_motor)
            self.enumRep += 1
        elif self.currentMsgMotor == self.lastMsgMotor and self.enumRep >= 3:
            msg_to_motor = ControlMessage(ControlMessage.SET_JOG, self.currentMsgMotor)
            self.msgIO.sendMessage(0, msg_to_motor)
            self.lastMsgMotor = self.currentMsgMotor
            self.enumRep = 0
        elif self.currentMsgMotor != self.lastMsgMotor and self.enumRep < 3:
            print("!=")
            self.enumRep = 0
            self.lastMsgMotor = self.currentMsgMotor

    def aiMode (self, msg):
        print("This is meant to be something")
    
    def cartMode(self,msg):
        '''This function moves to motors with using precise position in space'''
        print("This is meant to be something")
        

    # def jointMode(self, msg, rev):
    #     reverse = rev
    #     currentMsgMotor = [3]*0

    #     for id in range(0,4):
    #         currentMsgMotor[id] = self.__glovetomotor(msg[id+1])
    #     print("This is meant to be something")
    #     # currentMsgMotor = ControlMessage(ControlMessage.SET_JOIN_POSITION, currentMsgMotor)
    #     self.msgIO.sendMessage(0, currentMsgMotor)
    
    # def interMode (self, msg):
    #     return

    # def __glovetomotor(self, gloveValue):
    #     angleValue = gloveValue*90/100
    #     return angleValue










    

from enum import Enum
from Comm.ControlMessage import ControlMessage
from Comm import MessageIO

class translate:

    JOG = 1;
    JOINT = 2;
    CART = 3;
    AI = 4;
    INTERFACE = 5;

    lastMsg = [0,0,0,0]
    enumRep = 0

    # Forme du message recu par le gant
    # "Mode: ", "Flex : [4]", "IMU : [3]"

    def __init__(self, msgIO):
        self.msgIO = msgIO


    def chooseMode(self,msgGlove):
        '''This function analyses the message from the glove, determines the mode and calls the right translation function

        Parameters
        -------------
        msgGlove : double[] Data from the glove
        '''

        match msgGlove["Mode"]:
            case 1:
                print("this is jog mode")
                self.jogMode(msgGlove["Flex"], msgGlove["IMU"])
                
            case 2:
                print("this is joint mode")
            case 3:
                print("this is cartesian mode")
            case 4:
                print("this is AI mode")
            case 5:
                print("this is interface mode")

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
        msgMotor = [0,0,0,0]
        sumFinger = 0
        griperIncrement = 0

        # Verify the rotation of the hand associated with reversing direction
        if imu[2] <= treshold_IMU_neg:
            # Verify the flexion of the 3 fingers associated to joint 1,2,3
            for id in range(0,3):
                if flexion[id] >= tresholdFlex:
                    msgMotor[id] = -1
                    sumFinger += 1

            # Verify the flexion of the last finger associated with the gripper        
            if flexion[3] >= tresholdFlex and sumFinger == 3:
                if griperIncrement  == 0:
                    griperIncrement = 1
                elif griperIncrement == 1:
                    griperIncrement = 0
                msgMotor[3] = griperIncrement

        elif imu[2] >= treshold_IMU_pos:  
            # Verify the flexion of the 3 fingers associated to joint 1,2,3
            for id in range(0,3):
                if flexion[id] >= tresholdFlex:
                    msgMotor[id] = 1
                    sumFinger += 1

            # Verify the flexion of the last finger associated with the gripper        
            if flexion[3] >= tresholdFlex and sumFinger == 3:
                if griperIncrement  == 0:
                    griperIncrement = 1
                elif griperIncrement == 1:
                    griperIncrement = 0
                msgMotor[3] = griperIncrement

        else: pass

        if msgMotor == self.lastMsg and self.enumRep < 3:
            msg_to_motor = ControlMessage(ControlMessage.SET_JOG, self.lastMsg)
            self.msgIO.sendMessage(0, msg_to_motor)
            self.enumRep += 1
        elif msgMotor == self.lastMsg and self.enumRep >= 3:
            msg_to_motor = ControlMessage(ControlMessage.SET_JOG, msgMotor)
            self.msgIO.sendMessage(0, msg_to_motor)
            self.lastMsg = msgMotor
            self.enumRep = 0
        elif msgMotor != self.lastMsg and self.enumRep < 3:
            print("!=")
            self.enumRep = 0
            self.lastMsg = msgMotor

    def cartMode(self,msg):
        '''This function moves to motors with using precise position in space'''
        print("This is meant to be something")

    def aiMode (self, msg):
        print("This is meant to be something")

    # def jointMode(self, msg, rev):
    #     reverse = rev
    #     msgMotor = [3]*0

    #     for id in range(0,4):
    #         msgMotor[id] = self.__glovetomotor(msg[id+1])
    #     print("This is meant to be something")
    #     # msgMotor = ControlMessage(ControlMessage.SET_JOIN_POSITION, msgMotor)
    #     self.msgIO.sendMessage(0, msgMotor)
    
    # def interMode (self, msg):
    #     return

    def __glovetomotor(self, gloveValue):
        angleValue = gloveValue*90/100
        return angleValue










    

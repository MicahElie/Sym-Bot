from enum import Enum
from AI.AITrainer import AITrainer
from AI.DataCollector import DataCollector
from Comm import ControlMessage
from Comm.ControlMessage import ControlMessage
from Comm import MessageIO
import msvcrt

import numpy as np


class translate:
    '''This class represent the translation of a message accordinf to the mode chosen by the user.

    Attributes:
    ------------------
        lastMsgMotor :        The last translated message sent to the motors.
        currentMsgMotor :     The current message that is translated  bein sent to the motors.
        enumRep :             Counts everytime a message was repeated.
    
    '''

    JOG = 0;
    JOINT = 1;
    CART = 2;
    AI = 3;
    INTERFACE = 4;

    lastMsgMotor = [0,0,0,0]
    currentMsgMotor = [0,0,0,0]
    enumRep = 0
    file_database = "ai_database.txt"

    mode = 0
    flexion = [0,0,0,0]
    imu = [0,0,0]

    # Forme du message recu par le gant
    # "Mode: ", "Flex : [4]", "IMU : [3]"

    def __init__(self, msgIO):
        self.msgIO = msgIO
        self.AI = AITrainer(7, 10)
        #self.AI.read_data("filename")
        #self.AI.grad_descent(np.zeros((8, 10)), 0.2, 0.01)
        self.AI_dataCollector = DataCollector(7, 10)
        
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

        Parameters
        -------------
        msgGlove : Data from the glove
        '''
        if msgGlove['Mode'] == 1:
            self.mode = msgGlove['Mode']
            self.jogMode(msgGlove["Flex"], msgGlove["IMU"])
        elif msgGlove['Mode'] == 2:
            # print("this is joint mode")
            self.mode = msgGlove['Mode']
        elif msgGlove['Mode'] == 3:
            # print("this is cartesian mode")
            self.mode = msgGlove['Mode']
        elif msgGlove['Mode'] == 4:
            # print("this is AI mode")
            self.mode = msgGlove['Mode']
        elif msgGlove['Mode'] == 5:
            #Something awesome
            self.mode = msgGlove['Mode']



        # match msgGlove['Mode']:
        #     case 1:
        #         # print("this is jog mode")
        #         self.mode = msgGlove['Mode']
        #         self.jogMode(msgGlove["Flex"], msgGlove["IMU"])
                
        #     case 2:
        #         # print("this is joint mode")
        #         self.mode = msgGlove['Mode']

        #     case 3:
        #         # print("this is cartesian mode")
        #         self.mode = msgGlove['Mode']

        #     case 4:
        #         self.mode = msgGlove['Mode']
        #         self.aiMode(msgGlove['Flex'], msgGlove['IMU'])

        #     case 5:
        #         # print("this is interface mode")
        #         self.mode = msgGlove['Mode']


    def jogMode(self, flexion, imu):
        '''This function moves the motors as long as fingers are  in flexion
        
        Parameters
        --------------
        flexion : int Values associated with the four flexing fingers
        imu : double Values associated with the IMU which gives the direction of the hand
        '''
        tresholdFlex = 30
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
                print(griperIncrement)
                self.currentMsgMotor[3] = griperIncrement

            msg_to_motor = ControlMessage(ControlMessage.SET_JOG, self.currentMsgMotor)
            self.msgIO.sendMessage(0, msg_to_motor)


        elif imu[2] >= treshold_IMU_pos:  
            # Verify the flexion of the 3 fingers associated to joint 1,2,3
            for id in range(0,3):
                if flexion[id] >= tresholdFlex:
                    self.currentMsgMotor[id] = 1
                    sumFinger += 1

            # Verify the flexion of the last finger associated with the gripper        
            if flexion[3] >= tresholdFlex and sumFinger == 3:
                if griperIncrement  == 0:
                    griperIncrement = 1
                elif griperIncrement == 1:
                    griperIncrement = 0
                print(griperIncrement)
                self.currentMsgMotor[3] = griperIncrement
        
            msg_to_motor = ControlMessage(ControlMessage.SET_JOG, self.currentMsgMotor)
            self.msgIO.sendMessage(0, msg_to_motor)

        else: pass

        # if self.currentMsgMotor == self.lastMsgMotor and self.enumRep <= 3:
        #     msg_to_motor = ControlMessage(ControlMessage.SET_JOG, self.lastMsgMotor)
        #     self.msgIO.sendMessage(0, msg_to_motor)
        #     self.enumRep += 1
        # elif self.currentMsgMotor == self.lastMsgMotor and self.enumRep > 3:
        #     msg_to_motor = ControlMessage(ControlMessage.SET_JOG, self.currentMsgMotor)
        #     self.msgIO.sendMessage(0, msg_to_motor)
        #     self.lastMsgMotor = self.currentMsgMotor
        #     self.enumRep = 0
        # elif self.currentMsgMotor != self.lastMsgMotor:
        #     msg_to_motor = ControlMessage(ControlMessage.SET_JOG, self.lastMsgMotor)
        #     self.lastMsgMotor = self.currentMsgMotor
        #     self.enumRep = 0
        #This is a magnificent test


    def aiMode(self, flex, imu):
        '''This function moves the motors according to the hand symbols the user is making; 
        an AI recognise the right action even if there is variation
        
        Parameters:
        --------------------
        flex : int Values associated with the four flexing fingers
        imu : double Values associated with the IMU which gives the direction of the hand
        '''
        inputs = flex + imu
        matches = self.AI.evaluate(inputs).tolist()
        command = matches.index(max(matches))
        '''
        match command:
            case 1:
                pass
            case 2:
                pass
            #...
        '''

    def trainMode(self, flex, imu):
        '''This function registers current sensors values and saves them as
        training examples for the AI in a database

        Parameters:
        --------------------
        flex : int Values associated with the four flexing fingers
        imu : double Values associated with the IMU which gives the direction of the hand
        '''
        inputs = flex + imu
        if msvcrt.kbhit():
            action = msvcrt.getch()
            # inputs = flex + imu
            self.AI_dataCollector.save_new_position(self.file_database, inputs, action)
            action = input()
    
    def interMode (self, msg):
        pass

    # def jointMode(self, msg):

    #     msgMotor = ControlMessage(ControlMessage.SET_JOIN_POSITION, tabMsg)
    #     self.msgIO.sendMessage(0, msgMotor)
        

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

    # def cartMode(self,msg):
    # '''This function moves to motors with using precise position in space'''
    # print("This is meant to be something")


    # def __glovetomotor(self, gloveValue):
    #     angleValue = gloveValue*90/100
    #     return angleValue










    

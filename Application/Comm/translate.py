import threading
from enum import Enum
from time import sleep

from AI.AITrainer import AITrainer
from AI.DataCollector import DataCollector
from Comm import ControlMessage
from Comm.ControlMessage import ControlMessage
from Comm import MessageIO
# import msvcrt
import asyncio

import numpy as np


class translate:
    '''This class represent the translation of a message according to the mode chosen by the user.

    Attributes:
    ------------------
        lastMsgMotor :        The last translated message sent to the motors.
        currentMsgMotor :     The current message that is translated  bein sent to the motors.
        enumRep :             Counts everytime a message was repeated.
    
    '''

    TRAIN = -1
    JOG = 0
    JOINT = 1
    CART = 2
    AI_MODE = 3
    INTERFACE = 4

    # Special mode to train the AI. Keep "False" to run the system normally
    DEVELOPER_MODE = False

    # Number of consecutive identical readings (AI) required to start a new action
    ACTION_COUNT_MIN = 10
    action_count = 0
    last_command = -1

    lastMsgMotor = [0, 0, 0, 0]
    currentMsgMotor = [0, 0, 0, 0]
    griperIncrement = -1
    triggerGripper  = False
    enumRep = 0
    command = -1
    file_data_set = 'AI/Symbot_Data_Set.txt'

    mode = 0
    flexion = [0, 0, 0, 0]
    imu = [0, 0, 0]

    # Forme du message recu par le gant
    # "Mode: ", "Flex : [4]", "IMU : [3]"

    def __init__(self, msgIO):
        N_INPUTS = 5
        self.msgIO = msgIO
        self.AI = AITrainer(N_INPUTS, 10)
        if not self.DEVELOPER_MODE:
            self.AI.read_data(self.file_data_set)
            self.AI.grad_descent(np.zeros((N_INPUTS+1, 10)), 0.2, 0.01)
        self.AI_dataCollector = DataCollector(N_INPUTS, 10, self.file_data_set)
        self.commandThread = threading.Thread(target=self.manageAction)
        
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
        if self.DEVELOPER_MODE:
            self.mode = self.TRAIN
        elif not self.commandThread.isAlive():
            self.mode = msgGlove['Mode']
        flex = msgGlove["Flex"]
        imu = msgGlove["IMU"]

        if self.mode == self.TRAIN:
            # AI (Train) Mode
            self.trainMode(flex, imu)
        elif self.mode == self.JOG:
            # Jog Mode
            self.jogMode(flex, imu)
        elif self.mode == self.JOINT:
            # Joint Mode
            pass
        elif self.mode == self.CART:
            # Cartesian Mode
            pass
        elif self.mode == self.AI_MODE:
            # AI Mode
            self.aiMode(flex, imu)
        else:
            print("This mode is not available !")

    def jogMode(self, flexion, imu):
        '''This function moves the motors as long as fingers are  in flexion
        
        Parameters
        --------------
        flexion : int Values associated with the four flexing fingers
        imu : double Values associated with the IMU which gives the direction of the hand
        '''
        tresholdFlex = 30
        tresholdFlexMin = 10
        treshold_IMU_pos = 0.50
        treshold_IMU_neg = -0.50
        # [0, 360], [0, 90], [0, 180], [0, 180] -> Avoid getting to close to
        self.currentMsgMotor = [0,0,0,0]
        sumFinger = 0

        # Verify the rotation of the hand associated with reversing direction
        if imu[2] <= treshold_IMU_neg:
            # Verify the flexion of the 3 fingers associated to joint 1,2,3
            for id in range(0,3):
                if flexion[id] >= tresholdFlex:
                    self.currentMsgMotor[id] = -1
                    sumFinger += 1

            # Verify the flexion of the last finger associated with the gripper        
            if flexion[3] >= tresholdFlex:
                # for id in range(0,3):
                #     self.currentMsgMotor[id] = 0
                if self.triggerGripper:
                    self.griperIncrement    = -1 * self.griperIncrement
                    self.currentMsgMotor[3] = self.griperIncrement
                    self.triggerGripper     = False
            elif flexion[3] <= tresholdFlexMin:
                self.triggerGripper = True

            msg_to_motor = ControlMessage(ControlMessage.SET_JOG, self.currentMsgMotor)
            self.msgIO.sendMessage(0, msg_to_motor)

        elif imu[2] >= treshold_IMU_pos:  
            # Verify the flexion of the 3 fingers associated to joint 1,2,3
            for id in range(0,3):
                if flexion[id] >= tresholdFlex:
                    self.currentMsgMotor[id] = 1
                    sumFinger += 1

            # Verify the flexion of the last finger associated with the gripper        
            if flexion[3] >= tresholdFlex:
                # for id in range(0,3):
                #     self.currentMsgMotor[id] = 0
                if self.triggerGripper:
                    self.griperIncrement    = -1 * self.griperIncrement
                    self.currentMsgMotor[3] = self.griperIncrement
                    self.triggerGripper     = False
            elif flexion[3] <= tresholdFlexMin:
                self.triggerGripper = True
        
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
        self.lastMsgMotor = self.currentMsgMotor

    def aiMode(self, flex, imu):
        '''This function moves the motors according to the hand symbols the user is making; 
        an AI recognise the right action even if there is variation
        
        Parameters:
        --------------------
        flex : int Values associated with the four flexing fingers
        imu : double Values associated with the IMU which gives the direction of the hand
        '''
        if self.commandThread.isAlive():
            return

        inputs = flex + [imu[2]]
        matches = self.AI.evaluate(inputs).tolist()
        if max(matches) < 0.5:
            self.command = -1
        else:
            self.command = matches.index(max(matches))

        if self.command == self.last_command and self.command != -1:
            self.action_count = self.action_count + 1
        else:
            self.action_count = 0

        self.last_command = self.command

        if self.action_count > self.ACTION_COUNT_MIN:
            self.commandThread.start()
            self.action_count = 0

    def manageAction(self):
        '''Base function used by the command thread to control the message
        sent to the motors in AI mode
        '''
        mode = ControlMessage.SET_JOINT_POSITION
        command = self.command

        if command == 0:
            # GO_HOME
            mode = ControlMessage.GOTO_HOME
            msg = [0, 0, 0, 0]
        elif command == 1:
            # PICK
            msg = [[0, 45, 0, 170], [0, 0, 30, 170], [0, 0, 30, 30], [0, 45, 0, 30]]
        elif command == 2:
            # PUSH
            pass
        elif command == 3:
            # PULL
            pass
        elif command == 4:
            # REVERSE
            pass

        n_pos = len(msg)
        for i in range(n_pos):
            current_pos = msg[i]
            msg_to_motor = ControlMessage(mode, current_pos)
            self.msgIO.sendMessage(0, msg_to_motor)
            sleep(2)

    def trainMode(self, flex, imu):
        '''This function registers current sensors values and saves them as
        training examples for the AI in a database

        Parameters:
        --------------------
        flex : int Values associated with the four flexing fingers
        imu : double Values associated with the IMU which gives the direction of the hand
        '''
        inputs = flex + [imu[2]]
        self.AI_dataCollector.read_example(inputs)

    def interMode (self, msg):
        pass

    # def jointMode(self, msg):

    #     msgMotor = ControlMessage(ControlMessage.SET_JOINT_POSITION, tabMsg)
    #     self.msgIO.sendMessage(0, msgMotor)
        

    # def jointMode(self, msg, rev):
    #     reverse = rev
    #     currentMsgMotor = [3]*0

    #     for id in range(0,4):
    #         currentMsgMotor[id] = self.__glovetomotor(msg[id+1])
    #     print("This is meant to be something")
    #     # currentMsgMotor = ControlMessage(ControlMessage.SET_JOINT_POSITION, currentMsgMotor)
    #     self.msgIO.sendMessage(0, currentMsgMotor)
    
    # def interMode (self, msg):
    #     return

    # def cartMode(self,msg):
    # '''This function moves to motors with using precise position in space'''
    # print("This is meant to be something")


    # def __glovetomotor(self, gloveValue):
    #     angleValue = gloveValue*90/100
    #     return angleValue










    

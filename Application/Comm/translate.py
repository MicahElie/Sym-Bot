from enum import Enum
from AI import AITrainer
from Comm import ControlMessage
from Comm import MessageIO

import numpy as np


class translate:

    JOG = 1;
    JOINT = 2;
    CART = 3;
    AI = 4;
    INTERFACE = 5;

    # Forme du message recu par le gant
    # mode;index;majeur;annulaire;auriculaire;Y;Z;rotation;


    def __init__(self, length, msgIO):
        self.msgGlove = [length]
        self.msgIO = msgIO
        self.AI = AITrainer(7, 10)
        #self.AI.read_data("filename")
        #self.AI.grad_descent(np.zeros((8, 10)), 0.2, 0.01)

    def chooseMode(self,msgGlove):
        '''This function analyses the message from the glove, determines the mode and calls the right translation function

        Parameters
        -------------
        msgGlove : double[] Data from the glove
        '''
        self.msg = msgGlove.split(";")
        symbotMode = self.msg[0]

        match symbotMode:
            case 1:
                print("this is jog mode")
                self.jogMode(self.msg)
                
            case 2:
                print("this is joint mode")
            case 3:
                print("this is cartesian mode")
            case 4:
                print("this is AI mode")
                self.aiMode(self.msg)
            case 5:
                print("this is interface mode")

    def jogMode(self, msg, flexion, rev):
        '''This function moves the motors as long as fingers are  in flexion
        
        Parameters
        --------------
        msg : double[] Message from the glove
        flexion : double Value at which a finger is considered in flexion
        rev : double Value at which the hand is considered up-side-down
        '''
        flex = flexion
        reverse = rev
        tabMsg = [3]*0
        for id in range(0,3):
            if msg[id + 1] >= flex:
                tabMsg[id] = msg[id + 1]
            elif msg[id + 1] < flex:
                tabMsg[id] = msg[id + 1]
            else:
                print("Values from the glove not precise enough")
        
        if msg[8] >= reverse:
            for id in tabMsg:
                tabMsg[id] = tabMsg[id]*-1
        

        msgMotor = ControlMessage(ControlMessage.SET_JOG, tabMsg)
        self.msgIO.sendMessage(0, msgMotor)

    def jointMode(self, msg):

        msgMotor = ControlMessage(ControlMessage.SET_JOIN_POSITION, tabMsg)
        self.msgIO.sendMessage(0, msgMotor)
    
    def cartMode(self, msg):
        print("This is meant to be something")
    
    def aiMode (self, msg):
        print("This is meant to be something")
        inputs = msg[1:]
        matches = self.AI.evaluate(inputs)
        command = matches.index(max(matches))
        match command:
            case 1:
                pass
            case 2:
                pass
            #...
    
    def interMode (self, msg):
        pass








    

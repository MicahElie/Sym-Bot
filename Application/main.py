import threading
from Comm.BluetoothComm import Bluetooth
from Comm.translate import translate
from Comm.MessageIO import MessageIO
from Comm.driveManager import DriveManager
from test_translate import testTranslate

from Cinematic.PositionSolver import *
from Cinematic.JoinSystem import *
from Cinematic.RevoluteJoin import *
from Cinematic.robotAPI import *

class app:
    def __init__(self):
        
        self.commPort = None
        self.messageIO_Mot = MessageIO()
        self.messageIO_Gant = MessageIO()
        self.messageIO_Mot.addDevice(SerialComm("COM3", 57600))  #Port vers openCR
        # self.messageIO_Gant.addDevice(SerialComm("COM2", 57600))  #Port vers Pico
        self.driveManager = DriveManager([0, 0, 0, 0], self.messageIO_Mot)
        
        self.JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0.1283, 0]), [-math.pi/4, 2 * math.pi-0.4], hardwareStepDistance= math.pi*2/4096)])
        self.JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0.245, 0]), [-math.pi/4, 2 * math.pi-0.4], hardwareStepDistance= math.pi*2/4096))
        self.JS.addJoin(RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0.32824, 0]), [-math.pi/2-0.4, 2 * math.pi-0.4], hardwareStepDistance= math.pi*2/4096))


        self.robot = robotAPI(self.JS,[0., 0., 0.,0. ], self.driveManager)
        #self.robot.executeCommand(msg)

    '''
    def newConnection(self, conn):
        while True:
            self.commPort = EthernetComm(conn)
            self.messageIO.addDevice(self.commPort)
            while True:
                msg = self.messageIO.readMessage(1)
                if msg != None:
                    print("type:", msg.getType())
                    print("paload size: ", msg.getPayloadSize())
                    print("payload :", msg.getPayload())
                    self.robot.executeCommand(msg)
    '''

#Cette partie de code devrait être dans BluetoothComm
def todo(text):
    msg = {}
    msg['Mode'] = int(text[0])
    msg['Flex'] = [int(x) for x in text[1:5]]
    msg['IMU']  = [float(x) for x in text[5:8]]

    return msg

if __name__ == '__main__':

    commPort = None
    messageIO = MessageIO()
    Micah = translate(messageIO)
    messageIO.addDevice(SerialComm("COM7", 57600))  #Port vers open
    driveManager = DriveManager([0, 0, 0], messageIO)
    
    '''
    bt = BluetoothComm(1,1)
    while True:
        if bt.isMessageAvailable():
            msg = bt.readMessage()
            Micah.chooseMode(msg)
    '''

    ''' Comm USB '''
    serial = serial.Serial("COM6", 57600, timeout=1)
    # lastComm = [-10,-10]
    # delta = 3
    while True:
        while serial.in_waiting > 0:
            raw = serial.readline()
            comm = raw.decode().replace("\r\n", "").split(";")
            if len(comm) == 9:
                msg = todo(comm)
                Micah.chooseMode(msg)



    '''
    if((int(comm[0]) >= lastComm[0] + delta or int(comm[0]) <= lastComm[0] - delta) or 
        (int(comm[1]) >= lastComm[1] + delta or int(comm[1]) <= lastComm[1] - delta)):
        comm.split("")
    '''

    # if False:
    #     release1 = TestInteg.MotorTesting()
    #     release1.Motor_position_solo(1000)
    #     release1.Motor_position_all(1000)
    #     # release1.Motor_set_home(150)
    # else:
    #     commPort = None
    #     messageIO = MessageIO()
    #     messageIO.addDevice(SerialComm("COM3", 57600))  #Port vers open
    #     driveManager = DriveManager([0, 0, 0], messageIO)

            
    #     JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.Y, np.array([0.0, 0.0, 0.0]), [-math.pi/2, math.pi/2], hardwareStepDistance= math.pi*2/4096)])
    #     JS.addJoin(RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0.245, 0]), [-math.pi/4, math.pi/4], hardwareStepDistance= math.pi*2/4096))
    #     JS.addJoin(RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0.245, 0]), [-math.pi/4, math.pi/4], hardwareStepDistance= math.pi*2/4096))

    #     robot = robotAPI(JS,[0., 0., 0.], driveManager)
    #     print("Start")

    #     serial = serial.Serial("COM5", 115200, timeout=1)
    #     lastComm = [-10,-10]
    #     delta = 3
    #     while True:
    #         while serial.in_waiting > 0:
    #             comm = serial.readline().decode().replace("\r\n", "").split(";")
    #             if((int(comm[0]) >= lastComm[0] + delta or int(comm[0]) <= lastComm[0] - delta) or 
    #                 (int(comm[1]) >= lastComm[1] + delta or int(comm[1]) <= lastComm[1] - delta)):
    #                 # print(comm[0])
    #                 # print("test", tab)
    #                 # print(tab[0])
    #                 msg = ControlMessage(ControlMessage.SET_JOIN_POSITION, [0, int(comm[1])*10 + 1600, int(comm[0])*14])
    #                 robot.executeCommand(msg)

    #                 lastComm[0] = int(comm[0])
    #                 lastComm[1] = int(comm[1])

    # ---Test:---
    # val = 0
    # while val < 4096:
    #     msg = ControlMessage(ControlMessage.SET_JOIN_POSITION, [val, val, val])
    #     robot.executeCommand(msg)
    #     val = val + 128
    #     print(val)
    #     time.sleep(1)
    # print("msg")
    # msg = ControlMessage(ControlMessage.SET_JOIN_POSITION, [0, 0, 0])
    # print(msg)
    # robot.executeCommand(msg)

import math

from Comm.SerialComm import *
from Cinematic.PositionSolver import *
from Comm.ControlMessage import *

class robotAPI:
    def __init__(self, JS, basePosition, driveManager,gripperLimit=[170, 240]):
        self.JS = JS
        self.driveManager = driveManager
        self.solver = positionSolver()
        self.q = basePosition

        self.gripperMin = gripperLimit[0]
        self.gripperMax = gripperLimit[1]

    def findPosition(self, pos):
        pos = self.solver.solvePosition(joinSystem=self.JS, wantedPosition=pos, guessConfiguration=self.q,maxError=1)
        return pos

    def moveInCartesianTo(self, newPosition):
        newJoinPosition = self.findPosition(newPosition)
        if newJoinPosition is not None:
            print("fuck")
            hardWarePosition = self.JS.getHardwareJoinPosition( newJoinPosition)
            self.moveInJoinTo(hardWarePosition)

    def moveXWorld(self, dis):
        newPosition = self.JS.getLastJoinPosition(self.q) + np.array([dis, 0, 0]).reshape(3,1)
        self.moveInCartesianTo(newPosition)

    def moveYWorld(self, dis):
        newPosition = self.JS.getLastJoinPosition(self.q) + np.array([0, dis, 0]).reshape(3, 1)
        self.moveInCartesianTo(newPosition)

    def moveZWorld(self, dis):
        newPosition = self.JS.getLastJoinPosition(self.q) + np.array([0, 0, dis]).reshape(3, 1)
        self.moveInCartesianTo(newPosition)

    def moveInModelCoor(self,q):
        self.moveInJoinTo(self.JS.getHardwareJoinPosition(q))

    def moveInJoinTo(self, newJoinPosition):
        self.driveManager.setJoinPosition(newJoinPosition)
        self.q = newJoinPosition

    def getPosition(self, q):
        return self.JS.getLastJoinPosition(q)

    def setRobotState(self, q):
        self.q = q

    def openGripper(self, rate):
        self.driveManager.openGripper(rate)

    def closeGripper(self, rate):
        self.driveManager.closeGripper(rate)

    def setGripperPositionRate(self, rate):
        if rate > 1:
            rate = 1
        elif rate < 0:
            rate = 0

        position = math.floor(self.gripperMin + (self.gripperMax - self.gripperMin) * rate)

        self.driveManager.setGripperPosition(position)

    def setHomeStep(self, qHome):
        self.driveManager.setHome(qHome)

    def goToHome(self):
        self.driveManager.gotoHome()

    def setPositionModel(self, q):
        hardWarePosition = self.JS.getHardwareJoinPosition(q)
        self.moveInJoinTo(hardWarePosition)

    def setHomeModel(self, qHome):
        hardWarePosition = self.JS.getHardwareJoinPosition(qHome)
        self.setHomeStep(hardWarePosition)

    def executeCommand(self, controlMsg):
        if controlMsg.getType() == ControlMessage.SET_JOIN_POSITION:
            self.moveInJoinTo(controlMsg.getPayload())

        elif controlMsg.getType() == ControlMessage.SET_CARTESIAN_POSITION:
            self.moveInCartesianTo(controlMsg.getPayload())

        elif controlMsg.getType() == ControlMessage.SET_HOME:
            self.setHomeStep(controlMsg.getPayload())

        elif controlMsg.getType() == ControlMessage.OPEN_GRIPPER:
            self.openGripper(controlMsg.getPayload()[0])

        elif controlMsg.getType() == ControlMessage.CLOSE_GRIPPER:
            self.closeGripper(controlMsg.getPayload()[0])

        elif controlMsg.getType() == ControlMessage.GOTO_HOME:
            self.goToHome()

        elif controlMsg.getType() == ControlMessage.SET_HOME_MODEL:
            self.setHomeModel(controlMsg.getPayload())

        elif controlMsg.getType() == ControlMessage.SET_JOIN_POSITION_MODEL:
            self.setPositionModel(controlMsg.getPayload())

        elif controlMsg.getType() == ControlMessage.SET_GRIPPER_POSITION_RATE:
            self.setGripperPositionRate(controlMsg.getPayload()[0])



import unittest

from Cinematic.robotAPI import *
from Comm.driveManager import *
from test.TestComm.testCommDevice import *
from Cinematic.JoinSystem import *
from Cinematic.LinearJoin import *
from Cinematic.RevoluteJoin import *

class testRobotAPI(unittest.TestCase):

    def test_executeCommandSetHome(self):
        msgManager = self.createTestMessageIO()

        controller = [1, 1, 0]
        driveManager = DriveManager(controller, msgManager)

        JS = self.createTestJoinSystem()

        self.robot = robotAPI(JS, [1, 1, 1], driveManager)

        newHome = [40, 23, 11]

        msg = ControlMessage(ControlMessage.SET_HOME, newHome)
        self.robot.executeCommand(msg)

        test_msg_1 = msgManager.readMessage(0)
        test_msg_2 = msgManager.readMessage(1)

        test_ctrl_1 = [11]
        test_ctrl_2 = [40, 23]

        self.assertEqual(test_ctrl_1, test_msg_1.getPayload())
        self.assertEqual(ControlMessage.SET_HOME, test_msg_1.getType())

        self.assertEqual(test_ctrl_2, test_msg_2.getPayload())
        self.assertEqual(ControlMessage.SET_HOME, test_msg_2.getType())

    def test_executeCommandSetHome_Model(self):
        msgManager = self.createTestMessageIO()

        controller = [1, 1, 0]
        driveManager = DriveManager(controller, msgManager)

        JS = self.createTestJoinSystem()

        self.robot = robotAPI(JS, [1, 1, 1], driveManager)

        newHome = [0.5, 0.2, 0.1]

        msg = ControlMessage(ControlMessage.SET_HOME_MODEL, newHome)
        self.robot.executeCommand(msg)

        test_msg_1 = msgManager.readMessage(0)
        test_msg_2 = msgManager.readMessage(1)

        test_ctrl_1 = [10]
        test_ctrl_2 = [50, 20]

        self.assertEqual(test_ctrl_1, test_msg_1.getPayload())
        self.assertEqual(ControlMessage.SET_HOME, test_msg_1.getType())

        self.assertEqual(test_ctrl_2, test_msg_2.getPayload())
        self.assertEqual(ControlMessage.SET_HOME, test_msg_2.getType())

    def test_executeCommandGOTOHome(self):
        msgManager = self.createTestMessageIO()

        controller = [1, 1, 0]
        driveManager = DriveManager(controller, msgManager)

        JS = self.createTestJoinSystem()

        self.robot = robotAPI(JS, [1, 1, 1], driveManager)

        msg = ControlMessage(ControlMessage.GOTO_HOME)
        self.robot.executeCommand(msg)

        test_msg_1 = msgManager.readMessage(0)
        test_msg_2 = msgManager.readMessage(1)

        test_ctrl_1 = []
        test_ctrl_2 = []

        self.assertEqual(test_ctrl_1, test_msg_1.getPayload())
        self.assertEqual(ControlMessage.GOTO_HOME, test_msg_1.getType())

        self.assertEqual(test_ctrl_2, test_msg_2.getPayload())
        self.assertEqual(ControlMessage.GOTO_HOME, test_msg_2.getType())

    def test_executeCommandCloseGripper(self):
        msgManager = self.createTestMessageIO()

        controller = [1, 1, 0]
        driveManager = DriveManager(controller, msgManager, controllerIndexOfGripper=1)

        JS = self.createTestJoinSystem()

        self.robot = robotAPI(JS, [1, 1, 1], driveManager)

        rate = [100]

        msg = ControlMessage(ControlMessage.CLOSE_GRIPPER, rate)
        self.robot.executeCommand(msg)

        test_msg = msgManager.readMessage(1)
        test_ctrl = [100]

        self.assertEqual(test_ctrl, test_msg.getPayload())
        self.assertEqual(ControlMessage.CLOSE_GRIPPER, test_msg.getType())

    def test_executeCommandOpenGripper(self):
        msgManager = self.createTestMessageIO()

        controller = [1, 1, 0]
        driveManager = DriveManager(controller, msgManager, controllerIndexOfGripper=1)

        JS = self.createTestJoinSystem()

        self.robot = robotAPI(JS, [1, 1, 1], driveManager)

        rate = [100]

        msg = ControlMessage(ControlMessage.OPEN_GRIPPER, rate)
        self.robot.executeCommand(msg)

        test_msg = msgManager.readMessage(1)
        test_ctrl = [100]

        self.assertEqual(test_ctrl, test_msg.getPayload())
        self.assertEqual(ControlMessage.OPEN_GRIPPER, test_msg.getType())

    def test_executeSetGripperPositionRateMax(self):
        msgManager = self.createTestMessageIO()

        controller = [1, 1, 0]
        driveManager = DriveManager(controller, msgManager, controllerIndexOfGripper=1)

        JS = self.createTestJoinSystem()

        self.robot = robotAPI(JS, [1, 1, 1], driveManager, gripperLimit=[170, 240])

        rate = [100]

        msg = ControlMessage(ControlMessage.SET_GRIPPER_POSITION_RATE, rate)
        self.robot.executeCommand(msg)

        test_msg = msgManager.readMessage(1)
        test_ctrl = [240]

        self.assertEqual(test_ctrl, test_msg.getPayload())
        self.assertEqual(ControlMessage.SET_GRIPPER_POSITION, test_msg.getType())

    def test_executeSetGripperPositionRateMin(self):
        msgManager = self.createTestMessageIO()

        controller = [1, 1, 0]
        driveManager = DriveManager(controller, msgManager, controllerIndexOfGripper=1)

        JS = self.createTestJoinSystem()

        self.robot = robotAPI(JS, [1, 1, 1], driveManager, gripperLimit=[170, 240])

        rate = [0]

        msg = ControlMessage(ControlMessage.SET_GRIPPER_POSITION_RATE, rate)
        self.robot.executeCommand(msg)

        test_msg = msgManager.readMessage(1)
        test_ctrl = [170]

        self.assertEqual(test_ctrl, test_msg.getPayload())
        self.assertEqual(ControlMessage.SET_GRIPPER_POSITION, test_msg.getType())

    def test_executeSetGripperPositionRateHalf(self):
        msgManager = self.createTestMessageIO()

        controller = [1, 1, 0]
        driveManager = DriveManager(controller, msgManager, controllerIndexOfGripper=1)

        JS = self.createTestJoinSystem()

        self.robot = robotAPI(JS, [1, 1, 1], driveManager, gripperLimit=[170, 240])

        rate = [0.5]

        msg = ControlMessage(ControlMessage.SET_GRIPPER_POSITION_RATE, rate)
        self.robot.executeCommand(msg)

        test_msg = msgManager.readMessage(1)
        test_ctrl = [205]

        self.assertEqual(test_ctrl, test_msg.getPayload())
        self.assertEqual(ControlMessage.SET_GRIPPER_POSITION, test_msg.getType())


    def test_executeCommandSet_Join_Position(self):
        msgManager = self.createTestMessageIO()

        controller = [1, 1, 0]
        driveManager = DriveManager(controller, msgManager)

        JS = self.createTestJoinSystem()

        self.robot = robotAPI(JS, [1, 1, 1], driveManager)

        newPosition = [40, 23, 11]

        msg = ControlMessage(ControlMessage.SET_JOIN_POSITION, newPosition)
        self.robot.executeCommand(msg)

        test_msg_1 = msgManager.readMessage(0)
        test_msg_2 = msgManager.readMessage(1)

        test_ctrl_1 = [11]
        test_ctrl_2 = [40, 23]

        self.assertEqual(test_ctrl_1, test_msg_1.getPayload())
        self.assertEqual(ControlMessage.SET_JOIN_POSITION, test_msg_1.getType())

        self.assertEqual(test_ctrl_2, test_msg_2.getPayload())
        self.assertEqual(ControlMessage.SET_JOIN_POSITION, test_msg_2.getType())

    def test_executeCommandSet_Join_Position(self):
        msgManager = self.createTestMessageIO()

        controller = [1, 1, 0]
        driveManager = DriveManager(controller, msgManager)

        JS = self.createTestJoinSystem()

        self.robot = robotAPI(JS, [1, 1, 1], driveManager)

        newPosition = [40, 23, 11]

        msg = ControlMessage(ControlMessage.SET_JOIN_POSITION, newPosition)
        self.robot.executeCommand(msg)

        test_msg_1 = msgManager.readMessage(0)
        test_msg_2 = msgManager.readMessage(1)

        test_ctrl_1 = [11]
        test_ctrl_2 = [40, 23]

        self.assertEqual(test_ctrl_1, test_msg_1.getPayload())
        self.assertEqual(ControlMessage.SET_JOIN_POSITION, test_msg_1.getType())

        self.assertEqual(test_ctrl_2, test_msg_2.getPayload())
        self.assertEqual(ControlMessage.SET_JOIN_POSITION, test_msg_2.getType())


    def test_executeCommandSet_Join_Position_Model(self):
        msgManager = self.createTestMessageIO()

        controller = [1, 1, 0]
        driveManager = DriveManager(controller, msgManager)

        JS = self.createTestJoinSystem()

        self.robot = robotAPI(JS, [1, 1, 1], driveManager)

        newPosition = [0.5, 0.2, 0.1]

        msg = ControlMessage(ControlMessage.SET_JOIN_POSITION_MODEL, newPosition)
        self.robot.executeCommand(msg)

        test_msg_1 = msgManager.readMessage(0)
        test_msg_2 = msgManager.readMessage(1)

        test_ctrl_1 = [10]
        test_ctrl_2 = [50, 20]

        self.assertEqual(test_ctrl_1, test_msg_1.getPayload())
        self.assertEqual(ControlMessage.SET_JOIN_POSITION, test_msg_1.getType())

        self.assertEqual(test_ctrl_2, test_msg_2.getPayload())
        self.assertEqual(ControlMessage.SET_JOIN_POSITION, test_msg_2.getType())


    def createTestJoinSystem(self):
        JS = JoinSystem([LinearJoin(VectorSpaceAxis.X, np.array([0, 0, 0]), [0, 0.40])])
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0.275, 0]), [0, 2 * math.pi]))
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0.19, 0]), [0, 2 * math.pi]))
        return JS

    def createTestMessageIO(self):
        msgManager = MessageIO()
        msgManager.addDevice(testCommDevice(True))
        msgManager.addDevice(testCommDevice(True))
        return msgManager
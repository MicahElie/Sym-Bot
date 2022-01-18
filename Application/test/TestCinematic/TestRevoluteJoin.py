import unittest
import math
from Cinematic.RevoluteJoin import *
from test.TestCinematic.VectorTester import *


class TestRevoluteJoin(VectorTester):

    def test_initRevoluteX(self):
        join = RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0, 1]))

        self.assertEqual(join.rotationMatrix, getRotationMatrixX)

    def test_initRevoluteY(self):
        join = RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0, 1]))

        self.assertEqual(join.rotationMatrix, getRotationMatrixY)

    def test_initRevoluteZ(self):
        join = RevoluteJoin(VectorSpaceAxis.Z, np.array([0, 0, 1]))

        self.assertEqual(join.rotationMatrix, getRotationMatrixZ)

    def test_rotation(self):
        join = RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0, 1]))

        self.assertEqual(join.rotationMatrix(math.pi).all(), getRotationMatrixX(math.pi).all())

    def test_newJoinPosition(self):
        self.isNewJoinPositionWithCorrectShapeOk()
        self.isNewJoinPositionWithIncorrectShapeOk()

    def test_initLimitJoinLimit(self):
        self.initJoin(5, 1, 5, 1)
        self.initJoin(1, 5, 5, 1)

    def test_convertToHardwarePositionPositive(self):
        join = RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0, 1]),axisLimit=[0, 6], hardwareStepDistance=6/2000)
        self.assertEqual(0, join.convertToHardWarePosition(0))
        self.assertEqual(333, join.convertToHardWarePosition(1))
        self.assertEqual(1666, join.convertToHardWarePosition(5))

    def test_convertToHardwarePositionNegativeMinLimit(self):
        join = RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0, 1]),axisLimit=[-2, 4], hardwareStepDistance=6/2000)
        self.assertEqual(666, join.convertToHardWarePosition(0))
        self.assertEqual(1000, join.convertToHardWarePosition(1))
        self.assertEqual(1666, join.convertToHardWarePosition(3))

    def test_convertToHardwarePositionToModelPosition(self):
        join = RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0, 1]),axisLimit=[0, 6], hardwareStepDistance=6/2000)
        self.assertEqual(0, join.convertHardWarePositionToModelPosition(0))
        self.assertEqual(3, join.convertHardWarePositionToModelPosition(1000))
        self.assertEqual(0.15, join.convertHardWarePositionToModelPosition(50))

    def initJoin(self, argMax, argMin, expectedMax, expectedMin):
        join = RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0, 1]), [argMin, argMax])
        self.assertEqual(expectedMin, join.getMinLimit())
        self.assertEqual(expectedMax, join.getMaxLimit())

    def test_isLimitJoinLimitWorking(self):
        join = RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0, 1]), [5, 1])
        self.assertMatrixEqual(join.getRotationMatrix(5), join.getRotationMatrix(6))
        self.assertMatrixEqual(join.getRotationMatrix(4.1), join.getRotationMatrix(4.1))
        self.assertMatrixEqual(join.getRotationMatrix(0), join.getRotationMatrix(-6))

    def isNewJoinPositionWithIncorrectShapeOk(self):
        self.isNewJoinPositionOk(np.array([1, 0, 0]).reshape((3, 1)), np.array([1, 0, 0]).reshape((1, 3)))
        self.isNewJoinPositionOk(np.array([0, 1, 0]).reshape((3, 1)), np.array([0, 1, 0]).reshape((1, 3)))
        self.isNewJoinPositionOk(np.array([1, 0, 0]).reshape((3, 1)), np.array([1, 0, 0]).reshape((1, 3)))

    def isNewJoinPositionWithCorrectShapeOk(self):
        self.isNewJoinPositionOk(np.array([0, 0, 1]).reshape((3, 1)), np.array([0, 0, 1]))
        self.isNewJoinPositionOk(np.array([0, 1, 0]).reshape((3, 1)), np.array([0, 1, 0]))
        self.isNewJoinPositionOk(np.array([1, 0, 0]).reshape((3, 1)), np.array([1, 0, 0]))

    def isNewJoinPositionOk(self,expected, positionArray):
        joinX = RevoluteJoin(VectorSpaceAxis.X, positionArray)
        joinY = RevoluteJoin(VectorSpaceAxis.Y, positionArray)
        joinZ = RevoluteJoin(VectorSpaceAxis.Z, positionArray)

        self.assertVectorEqual(expected, joinX.getNextJoinRelativePosition(0))
        self.assertVectorEqual(expected, joinY.getNextJoinRelativePosition(0))
        self.assertVectorEqual(expected, joinZ.getNextJoinRelativePosition(0))

    def test_convertToHardwareReverseMode(self):
        join = RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0, 1]), axisLimit=[-2, 4], hardwareStepDistance=(6/2000), isJoinReverse=True)
        self.assertEqual(0, join.convertToHardWarePosition(4))
        self.assertEqual(1000, join.convertToHardWarePosition(1))
        self.assertEqual(333, join.convertToHardWarePosition(3))



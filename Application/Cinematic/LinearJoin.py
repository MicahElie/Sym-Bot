from Cinematic.vectorBase import *


class LinearJoin:
    def __init__(self,translationAxis, nextJoinRelativePosition, axisLimit = [0,10], hardwareStepDistance = 0.01, isJoinReverse = False):
        if translationAxis == VectorSpaceAxis.X:
            self.translationMatrix = translateX
        elif translationAxis == VectorSpaceAxis.Y:
            self.translationMatrix = translateY
        else:
            self.translationMatrix = translateZ

        self.rotationMatrix = np.eye(3)
        self.nexJoinRelativePosition = nextJoinRelativePosition.reshape((3, 1))

        if axisLimit[0] > axisLimit[1]:
            temp = axisLimit[0]
            axisLimit[0] = axisLimit[1]
            axisLimit[1] = temp

        self.axisMin = axisLimit[0]
        self.axisMax = axisLimit[1]

        self.hardwareStepDistance = hardwareStepDistance
        self.isJoinReverse = isJoinReverse

    def getRotationMatrix(self, state):
        return self.rotationMatrix

    def getNextJoinRelativePosition(self, joinState):
        if joinState > self.axisMax:
            return self.translationMatrix(self.nexJoinRelativePosition, self.axisMax)
        elif joinState < self.axisMin:
            return self.translationMatrix(self.nexJoinRelativePosition, self.axisMin)
        else:
            return self.translationMatrix(self.nexJoinRelativePosition, joinState)

    def convertToHardWarePosition(self, q):
        if self.isJoinReverse:
            return math.floor((self.axisMax-q) / self.hardwareStepDistance)
        else:
            return math.floor((q-self.axisMin)/self.hardwareStepDistance)

    def convertHardWarePositionToModelPosition(self, step):
        if self.isJoinReverse:
            return self.axisMax - step*self.hardwareStepDistance
        else:
            return self.axisMin + step*self.hardwareStepDistance


    def getMinLimit(self):
        return self.axisMin

    def getMaxLimit(self):
        return self.axisMax

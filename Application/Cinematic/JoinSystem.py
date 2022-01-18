from Cinematic.vectorBase import *


class JoinSystem:

    def __init__(self, allJoin = []):
        self.allJoin = allJoin

    def addJoin(self, newJoin):
        self.allJoin.append(newJoin)

    def getNbrJoin(self):
        return len(self.allJoin)

    def getLastJoinPosition(self, q):
        rotMatrix, lastJoinPosition = self.computeLastJoinPosition(q)
        return lastJoinPosition

    def getLastJoinPositionAndOrientation(self, q):
        rotMatrix, lastJoinPosition = self.computeLastJoinPosition(q)

        pose = np.concatenate((lastJoinPosition, rotMatrix), axis=None)
        return pose.reshape(12, 1)

    def computeLastJoinPosition(self, q):
        lastJoinPosition = np.array([0.0, 0.0, 0.0]).reshape(3, 1)
        rotMatrix = np.eye(3)
        for ctr in range(0, len(q)):
            rotMatrix = rotMatrix.dot(self.allJoin[ctr].getRotationMatrix(q[ctr]))
            lastJoinPosition += rotMatrix.dot(self.allJoin[ctr].getNextJoinRelativePosition(q[ctr]))
        return rotMatrix, lastJoinPosition

    def findPositionGradient(self, q, h=0.0001):
        gradient = None
        for x in range(0, len(q)):
            before = q.copy()
            after = q.copy()
            before[x] -= h
            after[x] += h
            delq = (self.getLastJoinPosition(after)-self.getLastJoinPosition(before))/(2*h)
            delq.reshape(3, 1)
            if gradient is None:
                gradient = delq
            else:
                gradient = np.concatenate((gradient, delq), axis=1)
        return gradient

    def computeGradientOfPositionBasedOnCostFuction(self, wantedPosition, q, costFunction, h=0.0001):
        gradient = None
        for x in range(0, len(q)):
            before = q.copy()
            after = q.copy()
            before[x] = float(before[x]) - h
            after[x] = float(after[x]) + h
            delq = (costFunction(wantedPosition, self.getLastJoinPosition(after)) - costFunction(wantedPosition, self.getLastJoinPosition(before))) / (2 * h)
            if gradient is None:
                gradient = delq
            else:
                gradient = np.concatenate((gradient, delq), axis=None)
        return gradient.reshape(len(q), 1)

    def convertHardWarePositionToModelPosition(self, q):
        hardwarePosition = []
        for ctr in range(0, len(q)):
            hardwarePosition.append(self.allJoin[ctr].convertHardWarePositionToModelPosition(q[ctr]))

        return hardwarePosition

    def getHardwareJoinPosition(self, q):
        hardwarePosition = []
        for ctr in range(0, len(q)):
            hardwarePosition.append(self.allJoin[ctr].convertToHardWarePosition(q[ctr]))

        return hardwarePosition



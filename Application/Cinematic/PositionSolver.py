import numpy as np

class positionSolver:
    def __init__(self):
        return

    def quadratiqueCostFunction(self, wanted, actual):
        error = 0
        for ctr in range(0, len(wanted)):
            deleta = (wanted[ctr]-actual[ctr])
            error += deleta*deleta
        return error

    def solvePosition(self, joinSystem, wantedPosition, guessConfiguration, rate=0.1, maxError = 0.001):
        wantedPosition = np.array(wantedPosition)
        q = np.array(guessConfiguration).reshape(len(guessConfiguration), 1)
        wantedPosition = wantedPosition.reshape(3, 1)
        for x in range(1, 50):
            J = joinSystem.computeGradientOfPositionBasedOnCostFuction(wantedPosition, q, self.quadratiqueCostFunction, h=0.000001)
            q = q-rate*J

        if max(np.abs(joinSystem.getLastJoinPosition(q)-wantedPosition)) <= maxError:
            return np.array(q)
        else:
            return None

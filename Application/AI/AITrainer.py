import math

import numpy as np


class AITrainer:

    def __init__(self, n, k):
        self.N = n  # Number of parameters (including constant term)
        self.K = k  # Number of possible actions
        self.theta = [0]*n
        self.x = np.zeros((1, n))
        self.y = np.zeros((1, k))

    def sigmoid(self, z):
        return 1 / (1 + math.exp(-z))

    def cost_function(self, theta):
        pass

    def read_data(self, filename):
        with open(filename) as file:
            for line in file:
                if line[0] != '#':
                    self.add_training_example(line)

    def add_training_example(self, line):
        data = line.split()

        y_ = [0]*self.K
        y_[int(data[0])] = 1
        self.y = np.vstack((self.y, np.array(y_)))

        x_ = [1]
        x_.extend(data[1:])
        self.x = np.vstack((self.x, np.array(x_)))




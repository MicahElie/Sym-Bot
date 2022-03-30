import math


class DataCollector:

    def __init__(self, n, k):
        self.N = n  # Number of inputs
        self.K = k  # Number of possible actions

    def collect_data(self, filename):
        action = input()
        while action != -1:
            msg = [0]  # Fetch sensors values
            inputs = msg[1:]  # flex + imu
            self.save_new_position(filename, inputs, action)  
            action = input()

    def save_new_position(self, filename, inputs, target_action=0):  # inputs: float vector, target_action: int

        if len(inputs) != self.N:
            return 1  # Invalid size for input vector
        if target_action < 0 or target_action >= self.K:
            return 2  # Invalid target action

        with open(filename, 'a') as f:
            f.write('\n' + str(target_action) + '  ')
            for i in inputs:
                f.write(str(i))
                f.write('  ')
        return 0

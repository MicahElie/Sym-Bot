import math
import threading
import time
from queue import Queue

class DataCollector:

    def __init__(self, n, k, filename):
        self.N = n  # Number of inputs
        self.K = k  # Number of possible actions
        self.Action = -1
        self.Filename = filename

    def my_input(self):
        self.Action = int(input())

    def read_example(self, inputs):
        action = '-1'
        #try:
        #    # action = inputimeout(prompt='I am prompt:', timeout=5)
        #    # action = self.wait_for_input('>>', time=5)
        #except TimeoutOccurred:
        #    print('No input read')
        ti = threading.Thread(target=self.my_input)
        # self.Action = int(action)
        ti.start()
        ti.join(0.01)

        if self.Action >= 0:
            self.save_new_position(inputs)

    def save_new_position(self, inputs):  # inputs: float vector, target_action: int

        if len(inputs) != self.N:
            return 1  # Invalid size for input vector

        if self.Action < 0 or self.Action >= self.K:
            return 2  # Invalid target action

        with open(self.Filename, 'a') as f:
            f.write('\n' + str(self.Action) + '  ')
            for i in inputs:
                f.write(str(i))
                f.write('  ')

        self.Action = -1
        print('Successfully added new training example : ')
        print(inputs)
        return 0

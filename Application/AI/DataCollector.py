import math
import asyncio

class DataCollector:

    def __init__(self, n, k, filename):
        self.N = n  # Number of inputs
        self.K = k  # Number of possible actions
        self.Action = -1
        self.Filename = filename

    async def read_action(self):
        self.Action = input()

    async def read_example(self, inputs):
        try:
            await asyncio.wait_for(self.read_action(), timeout=0.05)
        except asyncio.TimeoutError:
            print('No input read')

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
        return 0

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

    async def read_example(self, filename, inputs):
        try:
            await asyncio.wait_for(self.read_action(), timeout=0.5)
        except asyncio.TimeoutError:
            pass

        if self.Action >= 0:


        asyncio.create_task(self.read_action())

    def save_new_position(self, inputs, target_action):  # inputs: float vector, target_action: int

        if len(inputs) != self.N:
            return 1  # Invalid size for input vector

        if target_action < 0 or target_action >= self.K:
            return 2  # Invalid target action

        with open(self.Filename, 'a') as f:
            f.write('\n' + str(target_action) + '  ')
            for i in inputs:
                f.write(str(i))
                f.write('  ')
        return 0

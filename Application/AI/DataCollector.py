import math
import threading
import time
from queue import Queue

from inputimeout import inputimeout, TimeoutOccurred

class DataCollector:

    def __init__(self, n, k, filename):
        self.N = n  # Number of inputs
        self.K = k  # Number of possible actions
        self.Action = -1
        self.Filename = filename

    def _input(self, msg, q):
        ra = input(msg)
        if ra:
            q.put(ra)
        else:
            q.put("None")
        return

    def _slp(self, tm, q):
        time.sleep(tm)
        q.put("Timeout")
        return

    def wait_for_input(self, msg="Press Enter to continue", time=10):
        q = Queue()
        th = threading.Thread(target=self._input, args=(msg, q,))
        tt = threading.Thread(target=self._slp, args=(time, q,))

        th.start()
        tt.start()
        ret = None
        while True:
            ret = q.get()
            if ret:
                th._Thread__stop()
                tt._Thread__stop()
                return ret
        return ret

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

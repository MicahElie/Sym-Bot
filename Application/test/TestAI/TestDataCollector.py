from test.TestCinematic.VectorTester import *
from AI.DataCollector import *


class TestDataCollector(VectorTester):

    def test_write_example(self):
        inputs = [14, 1, 4, 31, 3, 7, -2]
        aitrainer = self.prepare_aitrainer(False)
        input_exp = np.array([1, 0.5920, 0.2459, 1.2323, 0.0365, 0.3358, -9.4305, 0.1084])
        input2 = aitrainer.X[4, :]
        self.assertVectorEqual(input_exp, input2)


if __name__ == '__main__':
    unittest.main()

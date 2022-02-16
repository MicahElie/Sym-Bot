from test.TestCinematic.VectorTester import *
from AI.AITrainer import *


class TestReadData(VectorTester):

    def test_classification_vector(self):
        aitrainer = AITrainer(8, 5)
        aitrainer.read_data('CSV_Data_Example.txt')
        self.assertMatrixEqual(np.array([[0, 1, 0, 0, 0],
                                         [0, 1, 0, 0, 0],
                                         [0, 0, 0, 1, 0]]),
                               aitrainer.Y)

    def test_input_vector(self):
        aitrainer = AITrainer(8, 5)
        aitrainer.read_data('CSV_Data_Example.txt')
        aitrainer.grad_descent(np.zeros((8, 5)), 0.01, 0)
        input_exp = np.array([1, 0.5920, 0.2459, 1.2323, 0.0365, 0.3358, -9.4305, 0.1084])
        input2 = aitrainer.X[1, :]
        self.assertVectorEqual(input_exp,
                               input2)


if __name__ == '__main__':
    unittest.main()

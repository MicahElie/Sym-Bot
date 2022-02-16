from test.TestCinematic.VectorTester import *
from AI.AITrainer import *


class TestReadData(VectorTester):

    def test_classification_vector(self):
        aitrainer = AITrainer(8, 5)
        aitrainer.read_data('CSV_Data_Example.txt')
        self.assertMatrixEqual(np.array([[0, 0, 0, 0, 0],
                                         [0, 1, 0, 0, 0],
                                         [0, 1, 0, 0, 0],
                                         [0, 0, 0, 1, 0]]),
                               aitrainer.y)

    def test_input_vector(self):
        self.assertEqual(True, True)


if __name__ == '__main__':
    unittest.main()

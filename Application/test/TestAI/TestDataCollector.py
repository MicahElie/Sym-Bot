from test.TestCinematic.VectorTester import *
from AI.DataCollector import *
import msvcrt


class TestDataCollector(VectorTester):

    def test_write_example(self):
        filename = "CSV_Writing_Example.txt"
        inputs1 = [14, 1, 4, 31, 3, 7, -2]
        inputs2 = [12.89745, 0.9837, 3.4875, 29.3985, 2.94854, 9.23598, -5.2455]
        aiDC = DataCollector(7, 10, filename)
        aiDC.save_new_position(inputs1, 2)
        aiDC.save_new_position(inputs2, 4)
        #test = 1
        #while not msvcrt.kbhit():
        #    print(test)
        #    test = test + 1
        #test = msvcrt.getch()
        # self.assertVectorEqual(input_exp, input2)

    async def read_action(self):
        filename = "CSV_Writing_Example.txt"
        aiDC = DataCollector(7, 10, filename)
        await asyncio.sleep(10)
        await asyncio.create_task(aiDC.read_example())
        print(aiDC.Action)

    def test_read_action(self):
        asyncio.run(self.read_action())


if __name__ == '__main__':
    unittest.main()

import unittest
from Comm.Accumulator import *
from Util.BytesUtil import *
from test.TestComm.testMessageManager import *


class testAccumulator(unittest.TestCase):
    def test_inisalisation(self):
        acc, msgManager = self.initAccumulator()
        self.assertEqual(AccumulatorState.READSTARTBYTES, acc.getState())

    def initAccumulator(self):
        msgManager = testMessageManager()
        acc = Accumulator(msgManager)
        return acc, msgManager

    def test_accumulateStartBytes(self):
        acc, msgManager = self.initAccumulator()
        acc.accumulate(IntToBytes(Frame.StartBytesValue))
        self.assertEqual(AccumulatorState.READTYPE, acc.getState())

    def test_accumulateType(self):
        acc, msgManager = self.initAccumulator()
        acc.accumulate(IntToBytes(Frame.StartBytesValue))
        acc.accumulate(IntToBytes(5))

        self.assertEqual(AccumulatorState.READPAYLOADSIZE, acc.getState())

    def test_accumulatePayloadSize(self):
        acc, msgManager = self.initAccumulator()
        acc.accumulate(IntToBytes(Frame.StartBytesValue))
        acc.accumulate(IntToBytes(5))
        acc.accumulate(IntToBytes(4))
        self.assertEqual(AccumulatorState.READPAYLOAD, acc.getState())

    def test_accumulatePayload(self):
        acc, msgManager = self.initAccumulator()
        self.accumaluteTestMessage(acc)

        self.assertEqual(AccumulatorState.READSTARTBYTES, acc.getState())

    def accumaluteTestMessage(self, acc):
        msgType = 5
        msg = "this is a comm test"
        msgBytes = bytearray(msg, encoding="UTF-8")
        acc.accumulate(IntToBytes(Frame.StartBytesValue))
        acc.accumulate(IntToBytes(msgType))
        acc.accumulate(IntToBytes(len(msgBytes)))
        acc.accumulate(msgBytes)

    def test_badStartBytes(self):
        acc, msgManager = self.initAccumulator()
        msgType = 5
        msg = "this is a comm test"
        msgBytes = bytearray(msg, encoding="UTF-8")
        msgPayloadSize = len(msgBytes)
        acc.accumulate(IntToBytes(0x55758963))
        acc.accumulate(IntToBytes(msgType))

        self.assertEqual(AccumulatorState.READSTARTBYTES, acc.getState())

        acc.accumulate(IntToBytes(msgPayloadSize))
        acc.accumulate(msgBytes)

        self.assertEqual(AccumulatorState.READSTARTBYTES, acc.getState())


    def test_isSendingFrameToMessageControl(self):
        acc, msgManager = self.initAccumulator()
        msgType = 5
        msg = "this is a comm test"
        msgBytes = bytearray(msg, encoding="UTF-8")
        msgPayloadSize = len(msgBytes)
        acc.accumulate(IntToBytes(Frame.StartBytesValue))
        acc.accumulate(IntToBytes(msgType))
        acc.accumulate(IntToBytes(msgPayloadSize))
        acc.accumulate(msgBytes)

        self.assertEqual(msgType, msgManager.RXFrame.getType())
        self.assertEqual(msgPayloadSize, msgManager.RXFrame.getPayloadSize())
        self.assertEqual(msgBytes, msgManager.RXFrame.getPayload())
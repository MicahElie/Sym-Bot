import unittest
from Comm.Frame import *
from Util.BytesUtil import *

class testFrame(unittest.TestCase):

    def test_init(self):
        frame = Frame()
        self.assertEqual(len(frame.buffer), Frame.MaxSize)

    def test_isWritingStartBytes(self):
        frame = Frame()
        self.assertEqual(Frame.StartBytesValue,frame.getStartBytes())

    def test_setTypeAndGetType(self):
        frame = Frame()
        frame.setType(1)
        self.assertEqual(1, frame.getType())

        frame.setType(0xFF023312)
        self.assertEqual(0xFF023312, frame.getType())

    def test_payloadSize(self):
        frame = Frame()
        frame.setPayloadSize(10)
        self.assertEqual(10, frame.getPayloadSize())

    def writeTestBytes(self, frame):
        frame.writeByteToPayload(1)
        frame.writeByteToPayload(2)
        frame.writeByteToPayload(3)
        frame.writeByteToPayload(4)
        frame.setPayloadSize(4)

    def test_writeBytesToPayload(self):
        frame = Frame()
        self.writeTestBytes(frame)
        self.assertEqual(4, len(frame.getPayload()))

    def test_writeBytesToPayload(self):
        frame = Frame()
        frame.writeBytesToPayload(IntToBytes(5))
        frame.setPayloadSize(4)
        self.assertEqual(IntToBytes(5), frame.getPayload())

    def test_resetPayload(self):
        frame = Frame()
        self.writeTestBytes(frame)

        self.assertEqual(4, len(frame.getPayload()))

        frame.resetPayload()
        self.assertEqual(0, len(frame.getPayload()))
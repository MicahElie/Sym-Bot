
class Frame:

    StartBytesValue = 0x00FF00FF
    StartByteIndex = 0
    StartByteSize = 4
    MaxSize = 1000
    TypeIndex = StartByteIndex + StartByteSize
    TypeSize = 4
    PayloadSizeIndex = TypeIndex + TypeSize
    PayloadIndexSize = 4
    PayloadIndex = PayloadSizeIndex + PayloadIndexSize



    def __init__(self, byteArray=None):
        if byteArray != None:
            self.buffer = byteArray
        else:
            self.buffer = bytearray(Frame.MaxSize)

        self.payloadCurrentIndex = Frame.PayloadIndex
        self.writeStartByte()


    def writeStartByte(self):
        self.writeInt(Frame.StartByteIndex,Frame.StartBytesValue)

    def getStartBytes(self):
        return self.readInt(Frame.StartByteIndex)

    def getType(self):
        return self.readInt(Frame.TypeIndex)
        return nbr

    def readInt(self, positionOfFirstByte):
        nbr = 0
        nbr |= self.buffer[positionOfFirstByte + 0] << 24
        nbr |= self.buffer[positionOfFirstByte + 1] << 16
        nbr |= self.buffer[positionOfFirstByte + 2] << 8
        nbr |= self.buffer[positionOfFirstByte + 3]
        return nbr

    def writeInt(self, positionOfFirstByte, value):
        self.buffer[positionOfFirstByte + 0] = (value & 0xFF000000) >> 24
        self.buffer[positionOfFirstByte + 1] = (value & 0x00FF0000) >> 16
        self.buffer[positionOfFirstByte + 2] = (value & 0x0000FF00) >> 8
        self.buffer[positionOfFirstByte + 3] = (value & 0x000000FF)

    def getPayloadSize(self):
        return self.readInt(Frame.PayloadSizeIndex)

    def setPayloadSize(self, value):
        self.writeInt(Frame.PayloadSizeIndex, value)

    def setType(self, value):
        self.writeInt(Frame.TypeIndex, value)

    def writeBytesToPayload(self, bytes):
        for byte in bytes:
            self.buffer[self.payloadCurrentIndex] = byte
            self.payloadCurrentIndex += 1

    def writeByteToPayload(self, byte):
        self.buffer[self.payloadCurrentIndex] = byte
        self.payloadCurrentIndex += 1

    def getPayload(self):
        return self.buffer[Frame.PayloadIndex:Frame.PayloadIndex+self.getPayloadSize()]

    def toBytes(self):
        return self.buffer[0:Frame.PayloadIndex+self.getPayloadSize()]

    def resetPayload(self):
        self.payloadCurrentIndex = Frame.PayloadIndex
        self.setPayloadSize(0)

    def __eq__(self, frame):
        return self.toBytes() == frame.toBytes()
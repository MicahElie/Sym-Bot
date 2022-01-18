import serial
import json


class SerialComm:
    def __init__(self, port, baud):
        self.port = port
        self.baud = baud
        self.serial = serial.Serial(port, baud, timeout=1)

    def sendJSon(self, JSon):
        j = (json.dumps(JSon)+'\n').encode()
        self.serial.write(j)


    def readJSon(self):
        rawJSon = self.serial.readline().decode()
        return json.loads(rawJSon)

    def isMessageAvailable(self):
        return self.serial.in_waiting > 0
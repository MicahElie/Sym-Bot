import bluetooth
# https://docs.python.org/3/library/socket.html#socket.socket.listen
import socket
# https://docs.python.org/3/library/struct.html
import struct

class Bluetooth:

    def __init__(self, mac, uuid):
        services = bluetooth.find_service(uuid=uuid, address=mac)
        first_match = services[0]
        self.port = first_match["port"]
        self.name = first_match["name"]
        self.host = first_match["host"]
        print("Connecting to \"{}\" on {}, port : {}".format(self.name, self.host, self.port))

        # Create the client socket
        self.sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        self.sock.connect((self.host, self.port))

        # self.sock = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
        # self.sock.connect((mac,self.port))

    def isMessageAvailable(self):
        print("Connected. Type something...")
        self.buffer = []
        while True:
            data = self.sock.recv(32)
            if not data:
                break
            self.buffer += data
            print("Received", data)

        if(len(self.buffer) == 17):
            return True
        else:
            return False

    def readMessage(self):
        msg = {}
        msg['Mode'] = self.buffer[0:1][0]
        msg['Flex'] = [self.buffer[1][0],self.buffer[2][0],self.buffer[3][0],self.buffer[4][0]]
        msg['IMU'] = [self.__convertBytesToFloat(self.buffer[5:9]), \
                      self.__convertBytesToFloat(self.buffer[9:13]), \
                      self.__convertBytesToFloat(self.buffer[13:17])]

        return msg

    def __convertBytesToFloat(self, datas):
        hexa = hex((datas[3][0]<<24)+(datas[2][0]<<16)+(datas[1][0]<<8)+(datas[0][0]))
        return struct.unpack('!f',bytes.fromhex(hexa[2:]))[0]

    def closeConnection(self):
        self.sock.close()
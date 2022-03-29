# import bluetooth
# https://docs.python.org/3/library/socket.html#socket.socket.listen
import socket
# https://docs.python.org/3/library/struct.html
import struct

# MAC = '58:BF:25:37:A6:9A'
# uuid = "00001101-0000-1000-8000-00805f9b34fb"

class Bluetooth:

    def __init__(self, mac, port=1, uuid=0):
        self.port = port
        self.host = mac
        '''
        services = bluetooth.find_service(uuid=uuid, address=mac)
        first_match = services[0]
        self.port = first_match["port"]
        self.name = first_match["name"]
        self.host = first_match["host"]
        print("Connecting to \"{}\" on {}, port : {}".format(self.name, self.host, self.port))

        # Create the client socket
        self.sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        self.sock.connect((self.host, self.port))
        '''
        self.sock = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
        self.sock.connect((mac, self.port))
        
    def isMessageAvailable(self):
        self.buffer = []

        data = self.sock.recv(64)
        self.buffer = data.decode()

        if(len(self.buffer) > 16 and self.buffer[-2:] == "\r\n"):
        # if(self.buffer[-2:] == "\r\n"):
            return True
        else:
            return False

    def readMessage(self):
        text = (self.buffer[:-3]).split(";")
        try:
            msg = {}
            msg['Mode'] = text[0]
            msg['Flex'] = text[1:5]
            msg['IMU']  = text[5:8]
        except (Exception):
            pass

        """
        msg['Mode'] = self.buffer[0:1][0]
        msg['Flex'] = [self.buffer[1][0],self.buffer[2][0],self.buffer[3][0],self.buffer[4][0]]
        msg['IMU'] = [self.__convertBytesToFloat(self.buffer[5:9]), \
                      self.__convertBytesToFloat(self.buffer[9:13]), \
                      self.__convertBytesToFloat(self.buffer[13:17])]
        """
        return msg

    def __convertBytesToFloat(self, datas):
        hexa = hex((datas[3][0]<<24)+(datas[2][0]<<16)+(datas[1][0]<<8)+(datas[0][0]))
        return struct.unpack('!f',bytes.fromhex(hexa[2:]))[0]

    def closeConnection(self):
        self.sock.close()
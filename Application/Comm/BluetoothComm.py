from wsgiref import validate
import bluetooth
# https://docs.python.org/3/library/socket.html#socket.socket.listen
import socket

# MAC = '58:BF:25:37:A6:9A'
# uuid = "00001101-0000-1000-8000-00805f9b34fb"

class Bluetooth:
    '''This class represents the bluetooth communication with a device; in this case, it's an ESP32

    Attributes:
    -------------
    This class doesn't have any attributes
    '''
    validateMsg = False

    def __init__(self, mac, port=1, uuid=0):
        ''' This function initialize all what's necessary for Bluetooth class to be functional

        Parameters:
        -------------
        mac :   string  Adress for connection
        port :  int     That's the communication port
        uuid :  string  Give the ID of what we want to communicate with     
        '''
        self.port = port
        self.host = mac
        
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
        '''
        
    def isMessageAvailable(self):
        '''This function verifies if a message is available
        
        Parameters:
        -----------------
        This function has no parameters
        '''
        self.buffer = []

        data = self.sock.recv(64)
        self.buffer = data.decode()

        if(len(self.buffer) > 16 and self.buffer[-2:] == "\r\n"):
        # if(self.buffer[-2:] == "\r\n"):
            return True
        else:
            return False

    def readMessage(self):
        '''It's pretty obvious what this function does
        
        Parameters:
        -----------------
        This function has no parameters
        '''
        self.validateMsg = False

        text = (self.buffer[:-3]).split("|")
        try:
            msg = {}
            msg['Mode'] = int(text[0])
            msg['Flex'] = [int(x) for x in text[1:5]]
            msg['IMU']  = [float(x) for x in text[5:8]]

            self.validateMsg = True
        except (Exception):
            pass

        return msg

    def isValidMsg(self):
        return self.validateMsg

    def closeConnection(self):
        self.sock.close()
import serial

from Comm.translate import translate
from Comm.MessageIO import MessageIO
from Comm.BluetoothComm import Bluetooth
from Comm.SerialComm import SerialComm

if __name__ == '__main__':

    # Select Communicatino's type between "USB" (Simuling UI) or "BT" (Glove)
    TypeComm = "USB" 

    commPort = None
    messageIO = MessageIO()
    Micah = translate(messageIO)
    messageIO.addDevice(SerialComm("/dev/ttyACM0", 57600))  #Port vers open

    if TypeComm == "BT":
        ''' Commmunicatino Bluetooth '''
        MAC_ = '58:BF:25:37:A6:9A'
        uuid_ = "00001101-0000-1000-8000-00805f9b34fb"
        bt = Bluetooth(MAC_,1,uuid_)
        while True:
            if bt.isMessageAvailable():
                msg = bt.readMessage()
                if bt.isValidMsg():
                    print(msg)
                    Micah.chooseMode(msg)

    elif TypeComm == "USB":
        ''' Communicatino USB '''
        Serial1 = SerialComm("/dev/ttyACM1", 57600)

        while True:
            while Serial1.isMessageAvailable():
                msg = Serial1.readMessage()
                if Serial1.isGoodMsg(msg):
                    msg = Serial1.getDigital()
                    print(msg)
                    Micah.chooseMode(msg)
    else:
        print(TypeComm + " not supported")
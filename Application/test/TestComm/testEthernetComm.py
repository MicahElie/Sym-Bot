import unittest
import socket
from Comm.Frame import *
from Comm.EthernetComm import *
from test.TestComm.testMessageManager import *
import threading

import time


class testEthernetComm(unittest.TestCase):

    def test_init(self):
        sock = socket.socket()
        comm = EthernetComm(sock)
        self.assertEqual(sock, comm.getSocket())

    def test_sendAndReadFrame(self):
        CommClient, CommServer = self.createServerAndClient()

        frame = Frame()
        frame.setType(1)
        payload = bytearray("this is a comm test", encoding="UTF-8")

        frame.setPayloadSize(len(payload))
        frame.writeBytesToPayload(payload)
        CommClient.sendFrame(frame)

        frameReceved = CommServer.readFrame()

        self.assertEqual(frame, frameReceved)

    def test_SendAndReadJSon(self):
        CommClient, CommServer = self.createServerAndClient()

        Json = self.createTestJson()
        CommClient.sendJSon(Json)

        recevedJSON = CommServer.readJSon()

        self.assertEqual(Json, recevedJSON)

    def test_isdataAvailable(self):
        CommClient, CommServer = self.createServerAndClient()
        Json = self.createTestJson()
        CommClient.sendJSon(Json)

        self.assertEqual(True, CommServer.isMessageAvailable())

    def test_waitForConnection(self):
        MsgManager = testMessageManager()

        x = threading.Thread(target=waitForConnection, args=("127.0.0.1" , 50000, 1, MsgManager,))
        x.start()

        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        client.connect(('127.0.0.1', 50000))
        time.sleep(1)

        self.assertTrue(MsgManager.connection != None)


    def createServerAndClient(self):
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind(('127.0.0.1', 50000))
        server.listen(1)
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect(('127.0.0.1', 50000))
        client.setblocking(False)
        conn, addr = server.accept()
        CommClient = EthernetComm(client)
        CommServer = EthernetComm(conn)
        return CommClient, CommServer

    def createTestJson(self):
        Json = {}
        Json["type"] = 1
        Json["data"] = [1, 2, 3, 4]
        return Json

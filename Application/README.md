# Sym-Bot : Application (Main Software)

## Table of Content
- [Getting started](#getting-started)
- [main.py](#main)
- [AI](#ai)
- [Comm](#comm)
  - [BluetoothComm](#bluetoothcomm)
  - [translate](#translate)
- [Test](#test)
  - [test_translate](#test-translate-class)

## Getting started
First, here's the hardware schematic that you have to keep in mind for every aspect of the project:

<img src="./img/Hardware_Schematic.PNG" alt="Hardware Schematic" width="512"/>

## main

## AI

## Comm
As you know, the Sym-Bot uses an ESP32, a Raspberry Pi 4 and an OpenCR Arduino microcontroler. All the code found in this section allows the communication between thoses devices to be functional. 
### BluetoothComm

### translate
When the bluetooth communication is established, it should receive messages in this form:
<div>
  <img src="./img/MessageReceived.png" alt="Message Received" width="512"/>
</div>
As you can see, this message receives the mode, the flexion state of four finger and information from the IMU. The strucutre used is a dictionnay whith the keys "Mode", "Flex" and "IMU".
- Modes are linked with the "chooseMode()" function. It is possible to add others modes if you want, but make sure to use numbers that are used in this function
- Flexion state are linked with the "Flex" key of the dictionnary and are used in every function of the translate class, depending on the way we want to translate the message
- Horizontal and vertical are not use in our application, but it could used ofr knowing how your hand moves, vertically and horizontally. It's is linked with the "IMU" key of the dictionnary
- Rotation is also linked with the "IMU" key and it is used to know if your hand is upside-down or not. It also used in every function of the translate class. In our particular case, the orientation of the hand indicates in which direction you want to control the motor.

As it was stated before, it is possible to add an other mode. It also means that you may want to add another function in the translate class. Here's how you should do it:
- Add mode in chooseMode() and execute the name of your new function in the if clause.
```
if msgGlove['Mode'] == modeNumber:
  self.mode = msgGlove['Mode']
  self.jogMode(msgGlove["oneOfTheKeys"], msgGlove["oneOfTheKeys"])
```
- Make sure to create the function linked with a new translation
```
def yourNewMode(self, "oneOfTheKeysYouSent", "oneOfTheKeysYouSent"):
  ##your new translation
```
- Make sure to send messages in the right format, using ControlMessage and MessageIO class(create a MessageIO object). These classes make your messages readable for the OpenCR. You also have to add a constant linked to your mode in ControlMessage.py
```
msg_to_motor = ControlMessage(ControlMessage.yourOwnConstant, self.youMessage)
self.msgIO.sendMessage(0, msg_to_motor)
```
Note that in our application, the message sent to the motors are in the form : `[motor1,motor2, motor3, servoMotor]`. In other words, its a message for each motor used

## Test
### test translate class



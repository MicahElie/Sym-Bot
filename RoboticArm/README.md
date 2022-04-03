# Sym-Bot : Robotic Arm

## Table of Content
- [Sym-Bot : Robotic Arm](#sym-bot--robotic-arm)
  - [Table of Content](#table-of-content)
  - [Environment](#environment)
  - [Calibration](#calibration)
  - [Control](#control)

## Environment
- Software : [Arduino IDE](https://www.arduino.cc/en/software)
- Add OpenCr board with instructions : https://emanual.robotis.com/docs/en/parts/controller/opencr10/#arduino-ide
- Add library ArduinoJson with Libray Manager
- Optional : Using [Visual Studio Code](https://code.visualstudio.com/) like a source-sode editor and add extension Arduino, publisher Microsoft

## Calibration
With monitor_m, we can get the different motor's position
1. Open Serial Monitor after to have upload the code
2. Write "begin [baudrate]" to initialise the communication with motor(s)
3. Write "scan [range]" to find the motor's id
4. Write "joint (id)" to set joint mode | Foreach motor
5. Write "torque (id) 0" to disable torque | Foreach motor
6. Position the robot at its zero
7. Write "position (id)" to get present position from motor | Foreach motor
8. Transcribe the resultat into main code, function init_dynamix()
9. Repeat step [6,8] for different position
10. If motor doesn't rotate in good direction, you can write "counter_clockwise (id)" or "clockwise (id)"

* Write what is in the quotation marks to Serial Monitor, [] => optional number and () => must number

## Control
Coming soon

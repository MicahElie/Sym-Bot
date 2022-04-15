# Sym-Bot : Motor Control

## Table of Content
- [Sym-Bot : Motor Control](#sym-bot--motor-control)
  - [Table of Content](#table-of-content)
  - [Environment](#environment)
  - [Calibration](#calibration)
  - [Control](#control)

## Environment
- Software : [Arduino IDE](https://www.arduino.cc/en/software) (1.8.19)
- Add OpenCr board (1.6.4) with instructions : https://emanual.robotis.com/docs/en/parts/controller/opencr10/#arduino-ide
- Add library ArduinoJson (6.18.5) with Libray Manager
- Optional : Using [Visual Studio Code](https://code.visualstudio.com/) like a source-sode editor and add extension Arduino, publisher Microsoft
- WARNING : The codes below used the versions mentioned in above (#.#.#).

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
With main, we can upload the code to control the robotic arm.

Before uploading the OpenCR Microcontroler code , make sur that the values defined in the init_dynamix() and init_servo() functions coresponds to your articulated arm implementation

<img src="ClassDiagram_Main.png" alt="Class Diagram Main">

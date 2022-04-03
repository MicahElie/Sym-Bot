# Sym-Bot : Robotic Arm by Hand Control  
[![License: GPL-3.0](https://img.shields.io/badge/License-GPLv3-blue.svg?style=flat-square)](https://github.com/chameau5050/Handling-Gro/main/LICENSE)
## Sherbrooke University, Robotic Engineering Program, 66th promotion, 2022

*Image de notre bras avec le gant pas trop loin*

## Table of Content
- [Sym-Bot : Robotic Arm by Hand Control](#sym-bot--robotic-arm-by-hand-control)
  - [Sherbrooke University, Robotic Engineering Program, 66th promotion, 2022](#sherbrooke-university-robotic-engineering-program-66th-promotion-2022)
  - [Table of Content](#table-of-content)
  - [Authors](#authors)
  - [Project context](#project-context)
  - [Objectives](#objectives)
  - [Important Note](#important-note)
  - [Recommandations](#recommandations)
    - [Mechanical](#mechanical)
    - [Electrical](#electrical)
    - [Software](#software)
  - [External Ressources](#external-ressources)
    - [MicroController](#microcontroller)
    - [Single board computer](#single-board-computer)
    - [Dynamixel Motors 1](#dynamixel-motors-1)
    - [Dynamixel Motors 2](#dynamixel-motors-2)
    - [ServoMotors](#servomotors)
    - [Power Supply](#power-supply)
    - [Flex Sensor](#flex-sensor)
    - [ESP32 microcontroller](#esp32-microcontroller)
    - [IMU](#imu)

## Authors
- Andrei Ioan Gabor - [TerrySpooker](https://github.com/TerrySpooker)
- Julien Thériault - [JuThe72](https://github.com/JuThe72)
- Yan-Éric Jérôme - [Arasmith](https://github.com/Arasmith)
- Frank Ciric Taicas - [Chromlox](https://github.com/Chromlox)
- Frédérick Boisvert - [boif1403](https://github.com/boif1403)
- Micah-Élie Labrecque - [MicahElie](https://github.com/MicahElie)

## Project context
This project came up from the desire to help people with disabilities to take or move objects out of reach. 
More pricesly, some of these people don't have enough strength in their arms to strech them out. Fortunately, most of the times, they can at least move their hands.
That's the core of the Symbot Project : Using a glove with sensors to control a robotic arm in the most intuitive way as possible, working in Symbiose with the user.

## Objectives
Our robotic arm is a simple 3 degrees of freedom robot. The goal is to accomplish simple tasks only by using the "Glove controler". Here are four things we want to do:
1. Push/Pull an object on table, placed in front of our robot
2. Turn an interuptor On/Off, the interuptor being on the table
3. Take a cellphone (200g max.) and keep it in the air
4. Using AI to predict moves based on hand signs that we created

## Important Note
Make sure to read all documentation linked with what you want to work on. 
We'll do anything we can for the documentation to be as clear as possible, but we can't garanty that it's going to work with your application.

## Recommandations
### Mechanical
* Most of the parts of our robot arm should be 3D-printed.
* We use different kind of bolts, shafts, plastic insert and couplers
* We created our own bearing with metalic balls; but you can easily modify this section
* For information about the assembly of the robotic arm, look at the [Mechanical section](/Material%20%26%20Assembly)

### Electrical
* Most of the electrical part should be for the implementation of sensor on the glove
* There must be enough space on the glove for all the electrical components
* The material of the glove must permit to sew the electrical components on it
* Make sure to use long enough wires for the connection between the motors and the OpenCR
* For more information about the Electrical design, look at the [Electrical Section of the robotic arm](/RoboticArmMotorControl/) and the [Electrical Section of glove](/UI)

### Software
* We mostly use Python and C/C++ with VS code as code editor
* For more information abour the Sofware design, look at the [Application section](/Application)

## External Ressources
This section lists all external ressources used in our projet
### MicroController
* Brand : [OpenCr](https://www.robot-advance.com/art-opencr1-0-robotis-2353.htm)
* Model : OpenCr
* Quantity : 1

### Single board computer
* Brand : [RaspBerry Pi](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/)
* Model : Raspberry PI 4 B
* Quantity : 1

### Dynamixel Motors 1
* Brand : [Dynamixel](https://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_workbench/)
* Model : XM430-W350
* Quantity : 1

### Dynamixel Motors 2
* Brand : [Dynamixel](https://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_workbench/)
* Model : XM430-W250
* Quantity : 2

### ServoMotors
* Brand : [HiTec](https://www.robotshop.com/ca/en/hitec-hs-422-servo-motor.html?gclid=CjwKCAjwlcaRBhBYEiwAK341jfIg3fw_xTxtCtNNNh4yNMYIuuqdtHVJHqRt-310Qe8wRKAHFg4d1xoCRGkQAvD_BwE)
* Model : HS-422
* Quantity : 1

### Power Supply
* Brand : [GlobTek inc.](https://www.digikey.ca/en/products/detail/globtek-inc/TR9CE7500LLP-IM-R6B/11201299?s=N4IgTCBcDaIOIBUCyBOAbCgDJgClgjBALoC%2BQA)
* Model : GTM96900P9012-T2
* Quantity : 1

### Flex Sensor
* Brand : [SparkFun](https://www.sparkfun.com/products/14666)
* Mdoel : SparkFun Qwiic Flex Glove Controller
* Quantity : 2

### ESP32 microcontroller
* Brand : [Espressif inc.](https://www.espressif.com/en/products/devkits/esp32-devkitc/overview)
* Model : DOIT ESP32 DEVKIT v1
* Quantity : 1 

### IMU
* Brand : [Grove](https://wiki.seeedstudio.com/Grove-IMU_9DOF_v2.0/)
* Model : IMU 9DOF v2.0
* Quantity : 1

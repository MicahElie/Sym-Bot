<div id="Handling GRO">
    <h1>Handling GRO</h1>
    <h3>Projet S4 Université de Sherbrooke</h3>
    <h3>UdeS-GRO | 65<sup>th</sup> Promotion | 2021</h3>
</div>

[//]: # (------------------------------------------------)

<div id="badges">
    

[![License: GPL-3.0](https://img.shields.io/badge/License-GPLv3-blue.svg?style=flat-square)](https://github.com/SPUdeS/SPUdeS/blob/main/LICENSE) 

</div>

[//]: # (------------------------------------------------)

**Decrire notre projet en quelques lignes
This is an academic project by robotics engineering undergraduates at Université de Sherbrooke.**
**Handling GRO is a five degrees of freedom fanuc robot. This is an academic project by robotics engineering undergraduates at l'Université de Sherbrooke.**

<div id="platform" align="center">
    <img src="./Documentation/imgage/Handling_GRO_image_robot.png" alt="Robot Assembly" width="703"/>
</div>

## Table of Contents
- [Setup](#Setup)
- [Documentation](#Documentation)
- [Platform Operation](#Operation)
- [External Resources](#Resources)
    - [Single-Board Computer](#Computer)
    - [Microcontroller](#Controller)
    - [Servomotors](#Servo)
    - [Power Supply: Motor/Arduino](#Power)
    - [Servo Rods](#Rods)


    
[//]: # (------------------------------------------------)

## <a id="Setup"></a>Setup
1. Buy the component in the [External Resources](#Resources) section.
2. Use the [CAD models](https://github.com/SPUdeS/SPUdeS/tree/main/CADs) to 3D print the [base](https://github.com/SPUdeS/SPUdeS/blob/main/CADs/Base.SLDPRT), the [platform](https://github.com/SPUdeS/SPUdeS/blob/main/CADs/Platform.SLDPRT) and the [servo arms](https://github.com/SPUdeS/SPUdeS/blob/main/CADs/Legs.SLDASM).
3. Do the electrical connections using the [electrical schematics](https://github.com/SPUdeS/SPUdeS/blob/main/Documentation/Electical%20schematics.pdf) in the documentation section.
3. Set up the [Raspberry Pi](#Computer) by connecting it with the [Arduino](#Controller), your computer and the to a power source.
4. Download or clone the repository in the Raspberry Pi.
5. Verify your Python version (3.5 and above) and the port series.
6. Build and transfer all the code to the Arduino and Raspberry Pi.
7. Open the interface and look at the [platform operation](#Operation) section.
## <a id="Documentation"></a>Documentation

The dynamic system can be found in the [Geometric model](https://github.com/SPUdeS/SPUdeS/tree/main/Geometric%20model) folder.
## <a id="Operation"></a>Platform Operation

The camera feed can show the Stewart platform instantly. The platform can be controlled using the following buttons on the interface:

<div id="Interface">
    <img src="./Documentation/img/InterfaceButtons.png" alt="Platform Assembly" width="264"/>
</div>

- It is possible to enter the angle value of all the motor (by default, all the motor should have the same angle).

- The Homing Button brings the stewart platform at its initial centered position.  

- The Move Up Button brings the stewart platform a bit over its actual position
## <a id="Resources"></a>External Resources
This section specifies the external resources used in the project.

#### <a id="Computer"></a>Single-Board Computer
- Brand: [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/)
- Model: Raspberry Pi 3 Model 3B+
- Quantity: 1

#### <a id="Controller"></a>Microcontroller
- Brand: [Arduino](https://store.arduino.cc/mega-2560-r3)
- Model: Mega 2560 REV3
- Quantity: 1

<!--#### <a id="Servo"></a>Servomotors
- Brand: [Hitec RCD](https://hitecrcd.com/products/servos/sport-servos/analog-sport-servos/hs-422/product)
- Model: HS-422
- Quantity: 6
-->
#### <a id="dynamixel"></a>Dynamixel_motors
- Brand: [Dynamixel](https://www.robotis.us/dynamixel-xm430-w350-r/)
- Model: XM430-W350
- Quantity: 4

#### <a id="SteperMotor"></a>SteperMotors
- Brand: [Elegoo](https://www.elegoo.com/products/elegoo-uln2003-5v-stepper-motor-uln2003-driver-board)
- Model: 28BYJ-48 
- Quantity: 1

#### <a id="DriveBoard"></a>DriveBoard
- Brand: [Elegoo](https://www.elegoo.com/products/elegoo-uln2003-5v-stepper-motor-uln2003-driver-board)
- Model: ULN2003 
- Quantity: 1
<!--
#### <a id="Servo"></a>Servomotors
- Brand: [Adafruit](https://www.amazon.ca/Adafruit-2201-Sub-micro-Servo-SG51R/dp/B0137LG0KW)
- Model: SG51R
- Quantity: 6

#### <a id="Power"></a>Power Supply: Motor/Arduino
- Brand: [CUI Inc.](https://www.digikey.com/en/products/detail/cui-inc/SWI10-5-N-P5/6618696)
- Model: SWI10-5-N
- Quantity: 1
-->
#### <a id="Rods"></a> Linear Rods
- Brand: [yqltd](https://www.amazon.ca/CNBTR-Horizontal-Bearing-Bushing-Optical/dp/B01KLE9QEU)
- ASIN: CNBTR4040 road
- Quantity: 2

#### <a id="linear_bearing"></a> Linear bearing
- Brand: [yqltd](https://www.amazon.ca/CNBTR-Horizontal-Bearing-Bushing-Optical/dp/B01KLE9QEU)
- ASIN: CNBTR4040 bearing
- Quantity: 4


## <a id="License"></a>License
This project is licenced under a  [![GPL-3.0](https://img.shields.io/badge/License-GPLv3-blue.svg?style=flat-square)](https://github.com/SPUdeS/SPUdeS/blob/main/LICENSE) license.

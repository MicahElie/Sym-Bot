#include <Arduino.h>
#include <SparkFun_ADS1015_Arduino_Library.h>
#include <MPU9250.h>
#include <Wire.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Mode:
uint8_t mode = 1;
// Flex Sensors:
ADS1015 pinkySensor;
ADS1015 indexSensor;
uint16_t hand_max[4] = {0, 0, 0, 0};
// Order for the right hand: {INDEX MIDDLE RING PINKY}
uint8_t hand[4] = {0, 0, 0, 0};
const uint16_t offset[4] = {0,0,0,190};
// IMU:
MPU9250 mpu;
// Order for data: {LINEAR_Y LINEAR_Z ROTATION_Z}
float data[3] = {0, 0, 0};

unsigned milliseconds = 100;

void setupBluetooth() {
  SerialBT.begin("ESP32-Symbot-Glove"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void setupFlexSensors(){
  //Set up each sensor, change the addresses based on the location of each sensor
  if (pinkySensor.begin(ADS1015_ADDRESS_SDA) == false) {
     Serial.println("Pinky not found. Check wiring.");
     while (1);
  }
  if (indexSensor.begin(ADS1015_ADDRESS_GND) == false) {
     Serial.println("Index not found. Check wiring.");
     while (1);
  }  
  pinkySensor.setGain(ADS1015_CONFIG_PGA_TWOTHIRDS); // Gain of 2/3 to works well with flex glove board voltage swings (default is gain of 2)
  indexSensor.setGain(ADS1015_CONFIG_PGA_TWOTHIRDS); // Gain of 2/3 to works well with flex glove board voltage swings (default is gain of 2)
  
  for (int finger = 0; finger < 2; finger++) {
    hand_max[finger] = indexSensor.getAnalogData(!finger);
    hand_max[finger + 2] = pinkySensor.getAnalogData(!finger);
  }
}

void setupIMUSensor(){
  mpu.setup(0x68);
  mpu.calibrateAccelGyro();
  mpu.setMagneticDeclination(-14);// la valeur de Sherbrooke
  // mpu.calibrateMag();
}

void flexSensorsData(){
  //Read and print our data
  for (int finger = 0; finger < 4; finger++){
    hand[finger] = 0;
  }
  for (int finger = 0; finger < 2; finger++) {
    if (indexSensor.getAnalogData(!finger) < hand_max[finger]){
      hand[finger] = hand_max[finger] - indexSensor.getAnalogData(!finger) - offset[finger];
    }
    if (pinkySensor.getAnalogData(!finger) < hand_max[finger + 2]){
      hand[finger + 2] = hand_max[finger + 2] - pinkySensor.getAnalogData(!finger) - offset[finger + 2];
    }
    // hand[finger] = indexSensor.getAnalogData(!finger);
    // hand[finger + 2] = pinkySensor.getAnalogData(!finger);
  }
  
  // Serial.println();
  // delay(100);
}

void serialIMUSensor(){

  
  if (mpu.update()) {
    // Serial.print("Rotations: \n(");
    // Serial.print(mpu.getYaw()); Serial.print(", ");
    // Serial.print(mpu.getPitch()); Serial.print(", ");
    // Serial.print(mpu.getRoll()); 
    // Serial.println(")");

    // Serial.print("Accelerations: \n(");
    // Serial.print(mpu.getAccX()); Serial.print(", ");
    // Serial.print(mpu.getAccY()); Serial.print(", ");
    // Serial.print(mpu.getAccZ()); 
    // Serial.println(")");
    
    // Serial.print("Gyro: \n(");
    // Serial.print(mpu.getGyroX()); Serial.print(", ");
    // Serial.print(mpu.getGyroY()); Serial.print(", ");
    // Serial.print(mpu.getGyroZ()); 
    // Serial.println(")");

    // Serial.print("Euler: \n(");
    // Serial.print(mpu.getEulerX()); Serial.print(", ");
    // Serial.print(mpu.getEulerY()); Serial.print(", ");
    // Serial.print(mpu.getEulerZ()); 
    // Serial.println(")");

    // Serial.print("Accelerations 2: \n(");
    // float accX = mpu.getLinearAccX();
    // if (accX <= 0.05f){
    //   accX = 0;
    // }
    // Serial.print(accX); Serial.print(", ");
    float accY = mpu.getLinearAccY();
    if (accY <= 0.05f)
      accY = 0;
    Serial.print(accY); Serial.print(", ");
    float accZ = mpu.getLinearAccZ();
    if (accZ <= 0.05f)
      accZ = 0;
    Serial.print(accZ);
    // Serial.println(")");

    // Serial.print("Bias: \n(");
    // Serial.print(mpu.getAccBiasX()); Serial.print(", ");
    // Serial.print(mpu.getAccBiasY()); Serial.print(", ");
    // Serial.print(mpu.getAccBiasZ()); 
    // Serial.println(")");

    // Serial.print("Mag: \n(");
    // Serial.print(mpu.getMagX()); Serial.print(", ");
    // Serial.print(mpu.getMagY()); Serial.print(", ");
    // Serial.print(mpu.getMagZ()); 
    // Serial.println(")");
  }
}

void serialSend(){
  Serial.print(mode + ";");
  for (int finger = 0; finger < 4; finger++){
    // Serial.print(finger);
    // Serial.print(": ");
    Serial.print(hand[finger]);
    SerialBT.print(hand[finger]);
    Serial.print(";");
    SerialBT.print(";");
  }
}
/*-------------------------------------------------- main fonctions --------------------------------------------------*/
void setup() {
  Wire.begin();
  Serial.begin(115200);
  setupBluetooth();
  delay(1000);

  // setupIMUSensor();
  setupFlexSensors();
}

void loop() {
  flexSensorsData();
  // serialIMUSensor();
  serialSend();
  Serial.println();
  SerialBT.println();
  delay(milliseconds);
}


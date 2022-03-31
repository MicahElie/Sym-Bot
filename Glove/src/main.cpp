#include <Arduino.h>
#include <SparkFun_ADS1015_Arduino_Library.h>
#include <MPU9250.h>
#include <Wire.h>
#include "BluetoothSerial.h"

// Pins:
const uint8_t LED = 2;
const uint8_t BUTTON = 23;

// Const:
const unsigned MILLISECONDS = 10;

// Mode:
uint8_t mode = 0;
uint8_t MODE_MAX = 4;
// Flex Sensors:
ADS1015 pinkySensor;
ADS1015 indexSensor;
uint16_t hand_max[4] = {0, 0, 0, 0};
uint16_t hand[4] = {0, 0, 0, 0}; // Order for the right hand: {INDEX MIDDLE RING PINKY}
const uint16_t offset[4] = {0,0,0,0};//190
// IMU:
MPU9250 mpu;
float imu[4] = {0, 0, 0}; // Order for data: {LINEAR_Y LINEAR_Z ROTATION_Z}

// Communication:
BluetoothSerial SerialBT;
String serialData;

/*-------------------------------------------------- setup fonctions --------------------------------------------------*/

void setupBluetooth() {
  SerialBT.begin("ESP32-Symbot-Glove"); //Bluetooth device name
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
}

void setupLED(){
  pinMode(LED, OUTPUT);
}

void buttonRead(){
  static uint8_t lastButtonState=0;
  static uint32_t debounceDelay = 10000;
  static uint32_t lastDebounceTime = 0;
  static uint8_t buttonState = 0;
  // read the state of the switch into a local variable:
  uint8_t reading = digitalRead(BUTTON);
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = micros();
  }
  if ((micros() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        mode = (mode+1) % MODE_MAX;
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

void setupButton(){
  pinMode(BUTTON, INPUT_PULLUP);
}

/*-------------------------------------------------- loop fonctions --------------------------------------------------*/

void flexSensorsData(){
  for (int finger = 0; finger < 4; finger++){
    hand[finger] = 0;
  }
  for (int finger = 0; finger < 2; finger++) {
    if (indexSensor.getAnalogData(!finger) < hand_max[finger]){
      hand[finger] = hand_max[finger] - indexSensor.getAnalogData(!finger) - offset[finger];
      if (hand[finger] > 100){
        hand[finger] = 0;
      }
    }
    if (pinkySensor.getAnalogData(!finger) < hand_max[finger + 2]){
      hand[finger + 2] = hand_max[finger + 2] - pinkySensor.getAnalogData(!finger) - offset[finger + 2];
      if (hand[finger + 2] > 100){
        hand[finger + 2] = 0;
      }
    }
  }
}

void IMUSensorData(){
  if (mpu.update()) {

    // Serial.print("Accelerations: \n(");
    // Serial.print(mpu.getAccX()); Serial.print(", ");
    // Serial.print(mpu.getAccY()); Serial.print(", ");
    // Serial.print(mpu.getAccZ()); 
    // Serial.println(")");

    // imu[0] += mpu.getLinearAccY()*9.81f*(milliseconds/1000.0); //Distance (Verifier l'axe X et Z pour voir si la main est bien plat => Z = 1.03 et X = 0.02 ou mettre un intervalle)
    if ((mpu.getAccY() >= 0.05f || mpu.getAccY() <= -0.05f) && mpu.getAccZ() > 0.85f){
      imu[0] += 0;
    }
    else {
      imu[0] += mpu.getLinearAccY()*9.81f*(MILLISECONDS/1000.0);
    }
      
    imu[1] = mpu.getLinearAccZ()*9.81f; //Height (Verifier l'axe X et Z pour voir si la main est bien plat => Z = 1.03 et X = 0.02 ou mettre un intervalle)
    if ((mpu.getAccY() >= 0.05f || mpu.getAccY() <= -0.05f) && mpu.getAccZ() > 0.85f){
      imu[1] = 0;
    }
    imu[2] = mpu.getAccZ(); //Rotation
    if (imu[2] <= 0.15f && imu[2] >= -0.15f){
      imu[2] = 0;
    }
    // imu[3] = mpu.getAccY(); //Rotation
    // if (imu[3] <= 0.01f && imu[3] >= -0.01f){
    //   imu[3] = 0;
    // }
  }
}

void activationLED(){
  if (imu[2] == 0.0f){
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
}

void stringToSend(){
  serialData = String(mode) + ";";

  for (int finger = 0; finger < 4; finger++){
  //   //serialData += finger + ":";
  //   // serialData += hand[finger] + ";";
    serialData += String(hand[finger]) + ";";
  }

  for (int i = 0; i < 3; i++){
    // switch(i){
    //   case 0:
    //     serialData += "Y:";
    //     break;
    //   case 1:
    //     serialData += "Z:";
    //     break;
    //   case 2:
    //     serialData += "R:";
    //     break;
    // }
    serialData += String(imu[i]) + ";";
  }
}

/*-------------------------------------------------- main fonctions --------------------------------------------------*/
void setup() {
  Wire.begin();
  Serial.begin(115200);
  setupBluetooth();
  delay(1000);

  setupLED();
  setupButton();
  setupIMUSensor();
  setupFlexSensors();
}

void loop() {
  flexSensorsData();
  IMUSensorData();
  activationLED();
  buttonRead();
  stringToSend();
  Serial.println(serialData);
  SerialBT.println(serialData);
  delay(MILLISECONDS);
}

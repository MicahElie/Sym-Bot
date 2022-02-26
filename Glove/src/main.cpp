#include <Arduino.h>
#include <SparkFun_ADS1015_Arduino_Library.h>
#include <BitBang_I2C.h>
#include <MPU9250.h>
#include <Wire.h>

#define SDA_PIN 6
#define SCL_PIN 7

// If you don't need the explicit device names displayed, disable this code by
// commenting out the next line
//
#define SHOW_NAME
#ifdef SHOW_NAME
const char *szNames[]  = {"Unknown","SSD1306","SH1106","VL53L0X","BMP180", "BMP280","BME280",
                "MPU-60x0", "MPU-9250", "MCP9808","LSM6DS3", "ADXL345", "ADS1115","MAX44009",
                "MAG3110", "CCS811", "HTS221", "LPS25H", "LSM9DS1","LM8330", "DS3231", "LIS3DH",
                "LIS3DSH","INA219","SHT3X","HDC1080","MPU6886","BME680", "AXP202", "AXP192", "24AA02XEXX", 
                "DS1307", "MPU688X", "FT6236G", "FT6336G", "FT6336U", "FT6436", "BM8563","BNO055"};
#endif

BBI2C bbi2c;
ADS1015 fingerSensor;
unsigned zeros[2] = {0, 0};

void setupFingersSensors(){
  Wire.begin();
  // BBI2C bbi2c;
  // bbi2c.bWire = 0;
  // bbi2c.iSDA = SDA_PIN;
  // bbi2c.iSCL = SCL_PIN;
  // I2CInit(&bbi2c, 100000);
  Serial.begin(115200);
  
  if (fingerSensor.begin(ADS1015_ADDRESS_SDA) == false) {
     Serial.println("Device not found. Check wiring.");
     while (1);
  } 
  
  fingerSensor.setGain(ADS1015_CONFIG_PGA_TWOTHIRDS); // Gain of 2/3 to works well with flex glove board voltage swings (default is gain of 2)
  zeros[0] = fingerSensor.getAnalogData(0);
  zeros[1] = fingerSensor.getAnalogData(1);
}

void loopFingersSensors(){
  uint16_t data;
  for (int finger = 0; finger < 2; finger++) {
    if (fingerSensor.getAnalogData(finger) >= zeros[finger]){
      data = 0;
    }
    else {
      data = zeros[finger] - fingerSensor.getAnalogData(finger);
    }
    // Serial.print(finger);
    // Serial.print(": ");
    if (data >= 100){
      data =100;
    }
    
    Serial.print(data);
    if(finger < 1)
      Serial.print(";");

  Serial.println();
  delay(200);    
  }
}

void setupI2Cbitbang(){
  memset(&bbi2c, 0, sizeof(bbi2c));
  bbi2c.bWire = 0; // use bit bang, not wire library
  bbi2c.iSDA = SDA_PIN;
  bbi2c.iSCL = SCL_PIN;
  I2CInit(&bbi2c, 100000L);
  delay(100); // allow devices to power up
}

void bitbang_I2C_Scan(){
  uint8_t map[16];
  uint8_t i;
  int iDevice, iCount;
  Serial.println("BIG LECHE");
  Serial.println("Starting I2C Scan");
  I2CScan(&bbi2c, map); // get bitmap of connected I2C devices
  if (map[0] == 0xfe) // something is wrong with the I2C bus
  {
    Serial.println("I2C pins are not correct or the bus is being pulled low by a bad device; unable to run scan");
  }
  else
  {
    iCount = 0;
    for (i=1; i<128; i++) // skip address 0 (general call address) since more than 1 device can respond
    {
      if (map[i>>3] & (1 << (i & 7))) // device found
      {
        iCount++;
        Serial.print("Device found at 0x");
        Serial.print(i, HEX);
        iDevice = I2CDiscoverDevice(&bbi2c, i);
        Serial.print(", type = ");
  #ifdef SHOW_NAME
        Serial.println(szNames[iDevice]); // show the device name as a string
  #else
        Serial.println(iDevice); // show the device name as the enum index
  #endif
      }
    } // for i
    Serial.print(iCount, DEC);
    Serial.println(" device(s) found");
  }
  delay(5000);
}

/*-------------------------------------------------- main --------------------------------------------------*/
void setup() {
  setupFingersSensors();
}

void loop() {
  loopFingersSensors();
}

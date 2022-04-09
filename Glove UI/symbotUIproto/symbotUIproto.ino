/**
 *  Simulate partially the glove and send data to Serial
 *    Button One      => Select mode
 *    Button Two      => LOW : Gripper close | HIGH : Gripper open
 *    Potentiometer 1 => Simulate Flex 1
 *    Potentiometer 2 => Simulate Flex 2
 *    Potentiometer 3 => Simulate Flex 3
 *    Potentiometer 4 => Simulate Hand's rotation (3th IMU's data)
 *
 *  Simulation with a ATmega2560 and gro420-shield
 *    gro420-shield : 
 *      - 4x potentiometer 10K
 *      - 2x switch push (button) | Pull-down with resistor 10K
 */

#include <stdint.h>

#define PIN_SW1 2
#define PIN_SW2 3
#define PIN_RV1 A0
#define PIN_RV2 A1
#define PIN_RV3 A2
#define PIN_RV4 A3

const uint8_t NB_FLEX = 4;
const uint8_t NB_IMU  = 3;

struct Msg{
  uint8_t Mode;
  uint8_t Flex[NB_FLEX];
  float   IMU[NB_IMU];
};
// Create & initiale message's datas
Msg msg = {1,0,0,0,0,0,0,0};

void fetchMode();
void fetchPot();
void fetchGrippper();
void fetchRotZ();
void sendMessage();

void setup() {
  // Configures Buttons Pin
  pinMode(PIN_SW1,INPUT);
  pinMode(PIN_SW2,INPUT);

  //Initialize serial and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  fetchMode();
  fetchPot();
  fetchGrippper();
  fetchRotZ();
  sendMessage();
}

// Simulate select mode with 1st button
void fetchMode(){
  static uint8_t lastButtonState=0;
  static uint32_t debounceDelay = 1000;
  static uint32_t lastDebounceTime = 0;
  static uint8_t buttonState = 0;
  
  // read the state of the switch into a local variable:
  uint8_t reading = digitalRead(PIN_SW1);

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

      // only change mode if the new button state is HIGH
      if (buttonState == HIGH) {
        msg.Mode = ++msg.Mode%5;
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

// Simulate Open/Close gripper with 2th button
void fetchGrippper(){
  static uint8_t lastButtonState=0;
  static uint32_t debounceDelay = 1000;
  static uint32_t lastDebounceTime = 0;
  static uint8_t buttonState = 0;
  
  // read the state of the switch into a local variable:
  uint8_t reading = digitalRead(PIN_SW2);

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

      // only toggle the gripper if the new button state is HIGH
      if (buttonState == HIGH) {
        msg.Flex[3] = msg.Flex[3] == 0 ? 100: 0;
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

// Simulate 3 first flex with 3 potentiometers
void fetchPot(){
  for(uint8_t i = 0; i < NB_FLEX-1 ; ++i){
    msg.Flex[i] = analogRead(i+PIN_RV1)*0.125;  // y = ((100-0)/(1024-0))*x
  }
}

// Simulate 3th IMU's data with 4th potentiometer
void fetchRotZ(){
  msg.IMU[2] = analogRead(PIN_RV4)*0.001953125-1.0; // y = ((1-(-1))/(1024-0))*x-1.0
}

void sendMessage(){
  static uint32_t lastTimeSend = 0;
  uint32_t timeSend = millis();

  // Send message @ 100 Hz
  if ((timeSend - lastTimeSend ) > 10) {
    lastTimeSend = timeSend;

    String data = String(msg.Mode)+";";
    for(uint8_t flex : msg.Flex)
      data += String(flex)+";";
    for(float imu : msg.IMU)
      data += String(imu)+";";
    Serial.println(data);
  }
}

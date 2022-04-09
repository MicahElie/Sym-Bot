#ifndef UNIT_TEST

#define DEBUG 0
#define DEBUG_MSG(msg)    // Serial.print(msg)
#define DEBUG_MSG_LN(msg) // Serial.println(msg)

#include <Arduino.h>

#include "SerialComm.h"
#include "ControlMessage.h"
#include "MessageIO.h"

#include "DynamixMotor.h"
#include "ServoMotor.h"

#define BAUD 57600

// Definition des defines pour les parametres des moteurs
// Definition of defines for engine parameters
#define NbrMotorDynamixel 3
#define NbrMotorServo 1
const uint8_t NBR_MOTOR = NbrMotorDynamixel + NbrMotorServo;

// Definition for used by the mode "INTERFACE"
enum CMD
{
  SET_LIMITES_INDEX = 1,
  SET_HOME_POSITION_INDEX = 3,
  SET_REFERENCE_POSITION_INDEX = 5,
  GO_TO_POSITION_INDEX = 7,
  GO_TO_HOME_INDEX = 9,
  RETURN_LIMITES_INDEX = 11,
  RETURN_HOME_POSITION_INDEX = 13,
  RETURN_REFERENCE_POSITION_INDEX = 15,
  RETURN_ACTUAL_POSITION_INDEX = 17,
  ACTION_ON_GRIPPER = 24,
  GO_TO_JOG = 77
};

MessageIO IO;
SerialComm SC(&Serial);

Motor *motors[NBR_MOTOR];

void init_dynamix();
void init_servo();

void setup()
{
  // Initialiser la communication Serial
  Serial.begin(BAUD);
  IO.addDevice(&SC);

  delay(10);

  init_dynamix();
  init_servo();
}

void loop()
{

  // Bloc de gestion des messages, communication
  ControlMessage *msg = IO.readMessage(0);
  if (msg != 0)
  {
    //Gestion du payload pour chaque moteur
    for (size_t i = 0; i < NBR_MOTOR; ++i)
    {
      //CODE POUR LES DIFFERENTES OPERATIONS A EFFECTUER PAR LE MOTEURS
      //CODE FOR THE DIFFERENT OPERATIONS TO BE CARRIED OUT BY THE ENGINES
      switch (msg->getType())
      {
      default:
        break;
      case GO_TO_POSITION_INDEX: //Set position = 7 SET_JOIN_POSITION
        motors[i]->go_to_degrees(msg->getPayload()[i]);
        break;
      case GO_TO_JOG: // Jog
        if (msg->getPayload()[i] == 1)
        {
          motors[i]->go_forward();
        }
        else if (msg->getPayload()[i] == -1)
        {
          motors[i]->go_backward();
        }
        else
        {
          // The arm doesn't move
        }
        break;
      case SET_LIMITES_INDEX: //Set limite = 1
        motors[i]->set_max_limit(msg->getPayload()[i]);
        break;
      case SET_HOME_POSITION_INDEX: //Set Home Position = 3
        motors[i]->set_home(msg->getPayload()[i]);
        break;
      case SET_REFERENCE_POSITION_INDEX: //Set reference position = 5
        break;
      case GO_TO_HOME_INDEX: //Go to HOME = 9
        motors[i]->go_to_home();
        break;

      //CODE TO RETURN INFORMATION
      case RETURN_LIMITES_INDEX: //return limites = 11
        msg->getPayload()[i] = (motors[i]->get_max_limit());
        break;
      case RETURN_HOME_POSITION_INDEX: //return HOME position = 13
        msg->getPayload()[i] = motors[i]->get_home();
        break;
      case RETURN_REFERENCE_POSITION_INDEX: //return reference position = 15
        msg->getPayload()[i] = motors[i]->get_zero();
        break;
      case RETURN_ACTUAL_POSITION_INDEX: //return actual position = 17
        msg->getPayload()[i] = (motors[i])->get_position();
        break;
      }
    }

    // delay(1000);
#if debug == 1
    ControlMessage responce(msg->getType() + 1, msg->getPayLoadSize(), msg->getPayload());
    IO.sendMessage(0, responce);
#endif
    delete msg;
  }
  else
  {
    //auto responce = ControlMessage(-1);
    //IO.sendMessage(0,responce);
  }
  delay(5);
}

void init_dynamix()
{
  const uint8_t IDs[] = {1, 2, 3};
  const uint16_t ZEROs[] = {10, 1360, 1024};
  const uint16_t HOMEs[] = {2047, 1920, 2048};
  const uint16_t MAXs[] = {4090, 2384, 3072};
  const uint16_t VELOCITYs[] = {128, 32, 32};
  const bool REVERSEs[] = {false, false, true};

  // Instanciation des Dynamix
  for (size_t m = 0; m < NbrMotorDynamixel; ++m)
  {
    if (motors[m] == nullptr)
    {
      motors[m] = new DynamixMotor(IDs[m], ZEROs[m], HOMEs[m], MAXs[m], VELOCITYs[m], REVERSEs[m]);
      DEBUG_MSG_LN("Set dynamix");
    }
  }

  // Go To Home
  for (size_t m = 0; m < NbrMotorDynamixel; ++m)
  {
    motors[m]->go_to_home();

    DEBUG_MSG("Homing  ");
    DEBUG_MSG_LN(m);
  }
}

void init_servo()
{
  const uint8_t IDs[] = {3};

  // Instanciation du Servo
  for (size_t m = NbrMotorDynamixel; m < NBR_MOTOR; ++m)
  {
    if (motors[m] == nullptr)
    {
      motors[m] = new ServoMotor(IDs[m-NbrMotorDynamixel]);
      DEBUG_MSG_LN("Set servomotor");
    }
  }

  // Go To Home
  for (size_t m = NbrMotorDynamixel; m < NBR_MOTOR; ++m)
  {
    motors[m]->go_to_home();

    DEBUG_MSG("Homing ");
    DEBUG_MSG_LN(m);
  }
}

#endif

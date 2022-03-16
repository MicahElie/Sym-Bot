#ifndef UNIT_TEST

#define DEBUG 0
#define DEBUG_MSG(msg)    // Serial.print(msg)
#define DEBUG_MSG_LN(msg) // Serial.println(msg)

#include <Arduino.h>
#include <ArduinoJson.h>
#include <String.h>

#include "SerialComm.h"
#include "ControlMessage.h"
#include "MessageIO.h"

#include "Motor.h"
#include "ServoMotor.h"

#define BAUD 57600

// Definition des defines pour les parametres des moteurs
// Definition of defines for engine parameters
#define NbrMotor 4
#define NbrMotorDynamixel 3
#define NbrMotorServo 1


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
  ACTION_ON_GRIPPER = 24
};

MessageIO IO;
SerialComm SC(&Serial);

Motor *Reference[NbrMotorDynamixel];
ServoMotor *ReferenceServo[NbrMotorServo];

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
    for (int i = 0; i < msg->getPayLoadSize(); i++)
    {
      //CODE POUR LES DIFFERENTES OPERATIONS A EFFECTUER PAR LE MOTEURS
      //CODE FOR THE DIFFERENT OPERATIONS TO BE CARRIED OUT BY THE ENGINES
      if (i >= NbrMotorDynamixel)
      {
      }
      else
      {
        switch (msg->getType())
        {
        default:
          break;
        case GO_TO_POSITION_INDEX: //Set position = 7 SET_JOIN_POSITION
          Reference[i]->go_to(msg->getPayload()[i]);
          break;
        case 77: // Jog
          if (msg->getPayload()[i] == 1)
          {
            Reference[i]->go_forward();
          }
          else if (msg->getPayload()[i] == -1)
          {
            Reference[i]->go_backward();
          }
          else
          {
            // The arm doesn't move
          }
          break;
        case SET_LIMITES_INDEX: //Set limite = 1
          Reference[i]->set_max_limit(msg->getPayload()[i]);
          break;
        case SET_HOME_POSITION_INDEX: //Set Home Position = 3
          Reference[i]->set_home(msg->getPayload()[i]);
          break;
        case SET_REFERENCE_POSITION_INDEX: //Set reference position = 5
          break;
        case GO_TO_HOME_INDEX: //Go to HOME = 9
          Reference[i]->go_to_home();
          break;
        case ACTION_ON_GRIPPER: //Action on gripper = 24
          if (i >= NbrMotorDynamixel && NbrMotorServo != 0)
          {
            int valeur = (int)((msg->getPayload()[i]) / 270.0 * 180.0);
            ReferenceServo[i]->go_to(valeur);
          }
          break;

        //CODE TO RETURN INFORMATION
        case RETURN_LIMITES_INDEX: //return limites = 11
          msg->getPayload()[i] = (Reference[i]->get_max_limit());
          break;
        case RETURN_HOME_POSITION_INDEX: //return HOME position = 13
          msg->getPayload()[i] = Reference[i]->get_home();
          break;
        case RETURN_REFERENCE_POSITION_INDEX: //return reference position = 15
          msg->getPayload()[i] = Reference[i]->get_zero();
          break;
        case RETURN_ACTUAL_POSITION_INDEX: //return actual position = 17
          msg->getPayload()[i] = (Reference[i])->get_position();
          break;
        }
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
  delay(100);
}

void init_dynamix()
{
  const uint8_t IDs[] = {1, 2, 3};
  const uint16_t ZEROs[] = {0, 1220, 80};
  const uint16_t HOMEs[] = {2047, 1780, 450};
  const uint16_t MAXs[] = {4095, 2300, 880};
  const bool REVERSEs[] = {false, true, true};

  // Instanciation des Dynamix
  for (size_t m = 0; m < NbrMotorDynamixel; ++m)
  {
    if (Reference[m] == nullptr)
    {
      Reference[m] = new Motor(IDs[m], ZEROs[m], HOMEs[m], MAXs[m], REVERSEs[m]);
      DEBUG_MSG_LN("Set dynamix");
    }
  }

  // Go To Home
  for (size_t i = 0; i < NbrMotorDynamixel; ++i)
  {
    Reference[i]->go_to_home();

    DEBUG_MSG("Homing  ");
    DEBUG_MSG_LN(i);
  }
}

void init_servo()
{
  const uint8_t IDs[] = {3};

  // Instanciation du Servo
  for (size_t m = 0; m < NbrMotorServo; ++m)
  {
    if (ReferenceServo[m] == nullptr)
    {
      ReferenceServo[m] = new ServoMotor(IDs[m]);
      DEBUG_MSG_LN("Set servomotor");
    }
  }

  // Go To Home
  for (size_t i = 0; i < NbrMotorServo; ++i)
  {
    ReferenceServo[i]->go_to_home();

    DEBUG_MSG("Homing ");
    DEBUG_MSG_LN(i);
  }
}

#endif

/*
 * COMMANDE DE TESTFOR UNIT TEST
{​​"type":7,"PLS":1,"data":[19389]}​​
{​​"type":7,"PLS":1,"data":[19389]}​​

{​​"type":11,"PLS":3,"data":[0,0,0]}​​
{​​"type":17,"PLS":3,"data":[0,0,0]}​​

{​​"type":17,"PLS":3,"data":[0,0,0]}​​

{​​"type":17,"PLS":2,"data":[0,0]}​​
{​​"type":3,"PLS":3,"data":[50,500,1500]}​​

{​​"type":5,"PLS":3,"data":[0,1,0]}​​

{​​"type":7,"PLS":3,"payload":[45,90,0]}​​
{​​"type":77,"PLS":3,"payload":[1,0,-1]}​​
*/

#ifndef UNIT_TEST

#define debug 0

#include <Arduino.h>
#include <ArduinoJson.h>
#include <String.h>
#include <DynamixelWorkbench.h>
#include <Servo.h>

#if defined(__OPENCM904__)
#define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
#define DEVICE_NAME ""
#endif

// #define STRING_BUF_NUM 64
// String cmd[STRING_BUF_NUM];

#include "SerialComm.h"
#include "ControlMessage.h"
#include "MessageIO.h"
// #include "TinyStepper_28BYJ_48.h"

#define BAUD 57600

MessageIO IO;
SerialComm SC(&Serial);

// Definition des defines pour la communication
// Definition of define for communication
#define SET_LIMITES_INDEX 1
#define SET_HOME_POSITION_INDEX 3
#define SET_REFERENCE_POSITION_INDEX 5
#define GO_TO_POSITION_INDEX 7
#define GO_TO_HOME_INDEX 9
#define RETURN_LIMITES_INDEX 11
#define RETURN_HOME_POSITION_INDEX 13
#define RETURN_REFERENCE_POSITION_INDEX 15
#define RETURN_ACTUAL_POSITION_INDEX 17
#define ACTION_ON_GRIPPER 24

// Definition des parametres important pour le fonctionnement des moteurs Dynamixel
// Definition of parameters important for the operation of Dynamixel motors
DynamixelWorkbench dxl_wb;
/* Pas utiliser | JuThe72
// uint8_t get_id[16];
// uint8_t scan_cnt = 0;
// uint8_t ping_cnt = 0;
// bool isAvailableID(uint8_t id);
// void split(String data, char separator, String* temp);
// void printInst();
*/
// Definition de la classe moteur pour les moteurs STEP
// Definition of the motor class for STEP motors
// TinyStepper_28BYJ_48 stepper;

// Definition de la classe moteur pour les moteurs SERVO
// Definition of the motor class for SERVO motors
Servo servo;

// Definition des defines pour les parametres des moteurs
// Definition of defines for engine parameters
#define NbrMotor 4
#define NbrMotorDynamixel 3
#define NbrMotorStepper 0
#define NbrMotorServo 1

// 3 moteur dynamixel et 1 servo(dans l'ordre) ; 7 = base, 13 = épaule, 1 = coude
int defineID[NbrMotor] = {7, 13, 1, 4};

// Limite de rotation maximal positif; en step
int LimiteMax[NbrMotor] = {4095, 2672, 1408, 2560};
int LimiteMin[NbrMotor] = {0, 1648, 0, 1536};

// Avec GetPosition
int Home[NbrMotor] = {2047, 2048, 1023, 2048};
int ReferencePosition[NbrMotor] = {0, 0, 0, 0};

int ActualPosition[NbrMotor] = {0, 0, 0, 0};
// Activer APPROCHE {0: Non | 1: Oui}
int initialisationAuDepart[NbrMotor] = {0, 0, 0, 0};
int PasInitialisation[NbrMotor] = {50, 50, 50, 50};
int PetitPasInitialisation[NbrMotor] = {10, 10, 10, 10};

// Pins d'interrupteur de fin de course
int inPinsInterupteurNumber[NbrMotor] = {11, 6, 7, 11};
// ...
int reverseInitialisation[NbrMotor] = {0, 0, 0, 0}; //0

//Définir les parametres pour les interrupteurs
/* Pas utilisee
// #define inpinsdynamixel 3
// #define nb_Step_for_dynamixel_moteur 506
// #define inpinstepp 3
// #define nb_Step_for_step_moteur 2048
*/
class motorservo
{
  int id;

public:
  motorservo(int id)
  {
    this->id = id;
    const int MOTOR_IN_PIN = 3;

    servo.attach(MOTOR_IN_PIN);
#if debug == 1
    if (servo.attached())
    {
      Serial.println("motor :");
      Serial.print(id);
      Serial.print(" ready.");
    }
    else
    {
      Serial.println("motor :");
      Serial.print(id);
      Serial.print(" non ready.");
    }
#endif
  };

  void gotoa(int32_t pos)
  {
    servo.write(pos);
  };

  void setHomingOffset(int32_t pos)
  {
#if debug == 1
    Serial.println(pos);
    Serial.println("Maybe, not avalable with this motor.");
#endif
  }

  int32_t GetPosition1()
  {
    long actualPos = servo.read();
    return actualPos;
  }

  int32_t GetReferencePosition1()
  {
#if debug == 1
    Serial.println("Maybe, not avalable with this motor.");
#endif
    return -1;
  }
};

/* class motorstepper
{
  public:
    motorstepper(int id)
    {
      const int LED_PIN = 13;
      const int MOTOR_IN1_PIN = 8;
      const int MOTOR_IN2_PIN = 9;
      const int MOTOR_IN3_PIN = 10;
      const int MOTOR_IN4_PIN = 11;
      const int STEPS_PER_REVOLUTION = 2048;

      stepper.connectToPins(MOTOR_IN1_PIN, MOTOR_IN2_PIN, MOTOR_IN3_PIN, MOTOR_IN4_PIN);

      //Code for setting motors in different modes
      //Code pour le réglage des moteurs dans differents modes
      stepper.setSpeedInStepsPerSecond(500);
      stepper.setAccelerationInStepsPerSecondPerSecond(500);
      #if debug == 1
          Serial.println("");
          Serial.print("If light On, steppermotor ");
          Serial.print(id);
          Serial.print(" ready. If light OFF, this steppermotor is NOT ready");
          Serial.println("");
      #endif
    };

    void gotoa(int32_t pos)
    {
      //stepper.moveRelativeInSteps(pos);
      stepper.moveToPositionInSteps(pos);
    };

    void setHomingOffset(int32_t pos)
    {
      #if debug == 1
          Serial.println("Fonction not working at 100%: Error");
          Serial.println("Maybe, not avalable with this motor.");
      #endif
      stepper.setCurrentPositionInSteps(pos);
    }

    int32_t GetPosition1()
    {
      long actualPos = stepper.getCurrentPositionInSteps();
      return actualPos;
    }

    int32_t GetReferencePosition1()
    {
      #if debug == 1
          Serial.println("Maybe, not avalable with this motor.");
      #endif
      return -1;
    }
}; */

// Definition de la classe moteur pour les moteurs dynamixel
// Definition of the motor class for dynamixel motors
// https://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_workbench/#opencr-and-opencm-tutorials
// https://emanual.robotis.com/docs/en/dxl/x/xl430-w250/#profile-acceleration108
// https://emanual.robotis.com/docs/en/dxl/x/xm430-w350/#goal-velocity104
// https://github.com/ROBOTIS-GIT/dynamixel-workbench/blob/09e31a8649a7d3b89d76b6bdd2df3407c1622a5c/dynamixel_workbench_toolbox/src/dynamixel_workbench_toolbox/dynamixel_item.cpp
class motor
{
private:
  int id;
  const char *log;
  uint16_t model_number;
  int baud = 57600;
  bool cmdSucceeded;

public:
  motor(int id)
  {
    // int actualPosition;
    // int goal = 100;
    // int32_t data;
    // const char *log;
    this->id = id;
    cmdSucceeded = dxl_wb.init(DEVICE_NAME, baud);
    cmdSucceeded = dxl_wb.ping((int8_t)id, &model_number, &log);

    //Code for setting motors in different modes
    //Code pour le réglage des moteurs dans differents modes
    //Essaie #1
    if (id == 1 || id == 13)
    {
      cmdSucceeded = dxl_wb.setReverseDirection(id, &log);
      #if debug == 1
        if (cmdSucceeded == 0)
        {
          Serial.println(log);
          Serial.println("Failed to change joint mode");
        }
        else
        {
          Serial.print("Succeed to change joint mode ");
        }
      #endif
    }

    cmdSucceeded = dxl_wb.jointMode(id, 75, 0, &log);
#if debug == 1
    if (cmdSucceeded == 0)
    {
      Serial.println(log);
      Serial.println("Failed to change joint mode");
    }
    else
    {
      Serial.print("Succeed to change joint mode ");
    }
#endif
    // Ou
    // cmdSucceeded = dxl_wb.setExtendedPositionControlMode(id, &log);
    /* Unit	0.229 [rev/min]	Sets velocity of the Profile
       * Unit	1 [msec]	Sets the time span for the Profile
       * Range	0 ~ 32767	‘0’ represents an infinite velocit */
    // cmdSucceeded = dxl_wb.itemWrite(id, "Profile_Velocity", 50, &log);
    /* Unit	214.577 [rev/min2]	Sets acceleration of the Profile
       * Unit	1 [msec]	Sets accelerating time of the Profile
       * Range	0 ~ 32767	‘0’ represents an infinite acceleration */
    // cmdSucceeded = dxl_wb.itemWrite(id, "Profile_Acceleration", 50, &log);
    /* cmdSucceeded = dxl_wb.torqueOn(id, &log);
      #if debug == 1
        if (cmdSucceeded == 1)
        {
          Serial.println("torque On ");
        }
        else
        {
          Serial.print("torque off");
        }
      #endif */
    // A ajouter pour plus de securite
    // cmdSucceeded = dxl_wb.itemWrite(id, "Max_Position_Limit", 4095, &log);
    // cmdSucceeded = dxl_wb.itemWrite(id, "Min_Position_Limit", 0, &log);

    //Essaie #2
    //cmdSucceeded = dxl_wb.setMultiTurnControlMode((int8_t)id,  &log);
    //Essaie #3
    //result1 = dxl_wb.setExtendedPositionControlMode((int8_t)id,  &log);
    //Essaie #4
    /* cmdSucceeded = dxl_wb.currentBasedPositionMode((int8_t)id, 100, &log);
      if (id != 0)
      {
        int resultss1 = dxl_wb.itemWrite(id, "Profile_Velocity", 50, &log);
        int resultss2 = dxl_wb.itemWrite(id, "Goal_PWM", 885, &log);
        int resultss3 = dxl_wb.itemWrite(id, "Goal_Velocity", 500, &log);
        int resultss4 = dxl_wb.itemWrite(id, "Goal_Current", 1193, &log);
        #if debug == 1
          if (resultss1 == 0 || resultss2 == 0 || resultss3 == 0 || resultss4 == 0)
          {
            Serial.println(log);
            Serial.println("Failed to set one of these setting: Profile_Velocity, Goal_PWM, Goal_Velocitu and Goal_Current ");
          }
          else
          {
            Serial.print("Succeed to set setting : Profile_Velocity, Goal_PWM, Goal_Velocitu and Goal_Current ");
          }
        #endif
      } */
    /* if (id == 0)
      {
        cmdSucceeded= dxl_wb.itemWrite(id, "Profile_Velocity", 20, &log);
        #if debug == 1
              if (cmdSucceeded == 0)
              {
                Serial.println(log);
                Serial.println("Failed to set reverse mode");
              }
              else
              {
                Serial.print("Succeed to set reverse mode ");
              }
        #endif
      } */

    // if (id != 5)
    // {
    /* cmdSucceeded = dxl_wb.torqueOn(id, &log);
        #if debug == 1
          if (cmdSucceeded == 1)
          {
            Serial.println("torque On ");
          }
          else
          {
            Serial.print("torque off");
          }
        #endif */
    // }

    cmdSucceeded = dxl_wb.ledOn((uint8_t)id, &log);
#if debug == 1
    if (cmdSucceeded == 1)
    {
      Serial.println("");
      Serial.print("Light On, motor ");
      Serial.print(id);
      Serial.print(" ready");
      Serial.println("");
    }
    else
    {
      Serial.println("");
      Serial.print("Light Off, motor ");
      Serial.print(id);
      Serial.print(" not ready");
      Serial.println("");
    }
#endif
  };

  void gotoa(int32_t pos)
  {
    dxl_wb.goalPosition((int8_t)id, (int32_t)pos, &log);
  };

  void setHomingOffset(int32_t pos)
  {
    cmdSucceeded = dxl_wb.itemWrite(id, "Homing_Offset", pos, &log);
#if debug == 1
    if (cmdSucceeded == false)
    {
      Serial.println(log);
      Serial.println("Failed to set Homing_Offset");
    }
    else
    {
      Serial.print("Succeed to set Homing_Offset");
    }
#endif
  }

  int32_t GetPosition1()
  {
    int32_t get_data = 0;
    cmdSucceeded = dxl_wb.itemRead(id, "Present_Position", &get_data, &log);
#if debug == 1
    if (cmdSucceeded == false)
    {
      Serial.println(log);
      Serial.println("Failed to get present position");
    }
    else
    {
      Serial.print("Succeed to get present position(value : ");
      Serial.print(get_data);
      Serial.println(")");
    }
#endif
    return get_data;
  }

  int32_t GetReferencePosition1()
  {
    int32_t get_data = 0;
    cmdSucceeded = dxl_wb.itemRead(id, "Homing_Offset", &get_data, &log);
#if debug == 1
    if (cmdSucceeded == false)
    {
      Serial.println(log);
      Serial.println("Failed to get Homing_Offset position");
    }
    else
    {
      Serial.print("Succeed to get Homing_Offset position(value : ");
      Serial.print(get_data);
      Serial.println(")");
    }
#endif
    return get_data;
  }
};

motor *Reference[NbrMotorDynamixel];
motorservo *ReferenceServo[NbrMotorServo];
// motorstepper *ReferenceStepper[NbrMotorStepper];

void setup()
{
  Serial.begin(BAUD);
  IO.addDevice(&SC);
  for (int PIN = 0; PIN < (NbrMotorDynamixel + NbrMotorStepper); PIN++)
  {
    pinMode(inPinsInterupteurNumber[PIN], INPUT);
  }
  delay(10);
}

void loop()
{
  // Instanciation des Dynamix
  for (int m = 0; m < NbrMotorDynamixel; m++)
  {
    if (Reference[m] == 0)
    {
      Reference[m] = new motor(defineID[m]);
#if debug == 1
      Serial.println("Je set un motor");
#endif
    }
  }

  // Instanciation du Servo
  for (int M = 0; M < NbrMotorServo; M++)
  {
    if (ReferenceServo[M] == 0)
    {
      ReferenceServo[M] = new motorservo(defineID[M]);
#if debug == 1
      Serial.println("Je set un servomotor");
#endif
    }
  }

  // Instanciation du Stepper
  /* for (int M = 0; M < NbrMotorStepper; M++)
  {
    if (ReferenceStepper[M] == 0)
    {
      ReferenceStepper[M] = new motorstepper(defineID[M]);
      #if debug == 1
            Serial.println("Je set un steppermotor");
      #endif
    }
  } */

  //INITIALISATION INITIALES DU ROBOT: MOTEUR DYNAMIXEL ET STEPPER
  for (int i = 0; i < (NbrMotor - NbrMotorServo); i++)
  {
    if (initialisationAuDepart[i] == 1)
    {
#if debug == 1
      Serial.println("debut de l<essaie avec les switch du moteur:");
      Serial.println(i);
#endif
      ActualPosition[i] = (Reference[i])->GetPosition1();
      int ajout = ActualPosition[i];

      //APPROCHE #1
      int readingstepper = digitalRead(inPinsInterupteurNumber[i]);
      while (readingstepper == 0)
      {
        if (reverseInitialisation[i] == 1)
        {
          ajout += PasInitialisation[i];
        }
        else
        {
          ajout -= PasInitialisation[i];
        }

        if (i < NbrMotorDynamixel)
        {
          Reference[i]->gotoa(ajout);
          delay(750);
        }
        /* else if (i >= NbrMotorDynamixel)
        {
          ReferenceStepper[i]->gotoa(ajout);
          delay(2000);
          //Je peut aussi set ca position actuelle comme je le veux
        } */
        readingstepper = digitalRead(inPinsInterupteurNumber[i]);
      }
      //APPROCHE #2
      delay(2000);
      if (reverseInitialisation[i] == 1)
      {
        ajout -= 4 * PetitPasInitialisation[i];
      }
      else
      {
        ajout += 4 * PetitPasInitialisation[i];
      }

      if (i < NbrMotorDynamixel)
      {
        Reference[i]->gotoa(ajout);
        delay(750);
      }
      /* else if (i >= NbrMotorDynamixel)
      {
        ReferenceStepper[i]->gotoa(ajout);
        delay(2000);
      } */
      //APPROCHE #3
      delay(750);
      int readingstepper_fine = digitalRead(inPinsInterupteurNumber[i]);
      while (readingstepper_fine == 0)
      {
        if (reverseInitialisation[i] == 1)
        {
          ajout += PetitPasInitialisation[i];
        }
        else
        {
          ajout -= PetitPasInitialisation[i];
        }

        if (i < NbrMotorDynamixel)
        {
          Reference[i]->gotoa(ajout);
          delay(500);
        }
        /* else if (i >= NbrMotorDynamixel)
        {
          ReferenceStepper[i]->gotoa(ajout);
          delay(1000);
          //Je peut aussi set ca position actuelle comme je le veux
        } */
        readingstepper_fine = digitalRead(inPinsInterupteurNumber[i]);
      }

      ActualPosition[i] = ajout;
      ReferencePosition[i] = ajout;
#if debug == 1
//Serial.println("La nouvelle valeur du home position pour step =");
//Serial.println(Home[i]);
#endif
    }
    initialisationAuDepart[i] = 0;
  }

  //INITIAL INITIALISATIO  FOR ROBOT: SERVOMOTOR
  //INITIALISATION INITIALES DU ROBOT: MOTEUR SRVO
  if (NbrMotorServo != 0)
  {
    int valeurservo = NbrMotorDynamixel + NbrMotorStepper;
    for (int ii = valeurservo; ii >= NbrMotor; ii++)
    {
      if (initialisationAuDepart[ii] == 1)
      {
        ReferenceServo[ii]->gotoa(0); //0 if the referenco position for SERVO?
        ActualPosition[ii] = 0;
        initialisationAuDepart[ii] = 0;
#if debug == 1
        Serial.println("Initialisation du servo ");
        Serial.println(ii);
        Serial.println("completer");
#endif
      }
    }
  }

  // Bloc de gestion des messages, communication
  ControlMessage *msg = IO.readMessage(0);
  if (msg != 0)
  {
    //Gestion du payload pour chaque moteur
    for (int i = 0; i < msg->getPayLoadSize(); i++)
    {
      //CODE POUR LES DIFFERENTES OPERATIONS A EFFECTUER PAR LE MOTEURS
      //CODE FOR THE DIFFERENT OPERATIONS TO BE CARRIED OUT BY THE ENGINES

      //Set position = 7 SET_JOIN_POSITION
      if (msg->getType() == GO_TO_POSITION_INDEX)
      {
        if (msg->getPayload()[i] >= LimiteMax[i])
        {
          msg->getPayload()[i] = LimiteMax[i];
        }

        if (msg->getPayload()[i] <= LimiteMin[i])
        {
          msg->getPayload()[i] = LimiteMin[i];
        }

        ActualPosition[i] = msg->getPayload()[i] + ReferencePosition[i];
        if (i < NbrMotorDynamixel)
        {
          if (reverseInitialisation[i] == 1)
          {
            Reference[i]->gotoa(ReferencePosition[i] - (msg->getPayload()[i]));
          }
          else
          {
            Reference[i]->gotoa(ReferencePosition[i] + msg->getPayload()[i]);
          }
          ActualPosition[i] = (Reference[i])->GetPosition1();
        }
        /* else if (i >= NbrMotorDynamixel)
        {
          ReferenceStepper[i]->gotoa(msg->getPayload()[i]);
          ActualPosition[i] = msg->getPayload()[i];
        } */
      }

      //Set position = 77: La nouvelle fonction GoTo sans la section
      if (msg->getType() == 77)
      {
        // int valeurRecu = msg->getPayload()[i];
        // int valeurModifier = 0;

        if (i < NbrMotorDynamixel)
        {
          Reference[i]->gotoa(msg->getPayload()[i]);
        }
        /* else if (i >= NbrMotorDynamixel)
        {
          ReferenceStepper[i]->gotoa(msg->getPayload()[i]);
        } */
      }
      //Set limite = 1
      else if (msg->getType() == SET_LIMITES_INDEX)
      {
        LimiteMax[i] = msg->getPayload()[i];
      }
      //Set Home Position = 3
      else if (msg->getType() == SET_HOME_POSITION_INDEX)
      {
        Home[i] = msg->getPayload()[i];
      }
      //Set reference position = 5
      else if (msg->getType() == SET_REFERENCE_POSITION_INDEX)
      {
        Serial.println("debut de l<essaie avec les switch du moteur:");
        Serial.println(i);
        if (msg->getPayload()[i] == 1)
        {
          ActualPosition[i] = (Reference[i])->GetPosition1();
          int ajout = ActualPosition[i];
          //APPROCHE #1
          int readingstepper = digitalRead(inPinsInterupteurNumber[i]);
          Serial.println(readingstepper);
          while (readingstepper == 0)
          {
            if (reverseInitialisation[i] == 1)
            {
              ajout += PasInitialisation[i];
            }
            else
            {
              ajout -= PasInitialisation[i];
            }

            if (i < NbrMotorDynamixel)
            {
              Reference[i]->gotoa(ajout);
              delay(750);
            }
            /* else if (i >= NbrMotorDynamixel)
            {
              ReferenceStepper[i]->gotoa(ajout);
              delay(2000);
              //Je peut aussi set ca position actuelle comme je le veux
            } */
            readingstepper = digitalRead(inPinsInterupteurNumber[i]);
          }
          //APPROCHE #2
          delay(2000);
          if (reverseInitialisation[i] == 1)
          {
            ajout -= 4 * PetitPasInitialisation[i];
          }
          else
          {
            ajout += 4 * PetitPasInitialisation[i];
          }

          if (i < NbrMotorDynamixel)
          {
            Reference[i]->gotoa(ajout);
            delay(750);
          }
          /* else if (i >= NbrMotorDynamixel)
          {
            ReferenceStepper[i]->gotoa(ajout);
            delay(2000);
          } */
          //APPROCHE #3
          delay(750);
          int readingstepper_fine = digitalRead(inPinsInterupteurNumber[i]);
          while (readingstepper_fine == 0)
          {
            if (reverseInitialisation[i] == 1)
            {
              ajout += PetitPasInitialisation[i];
            }
            else
            {
              ajout -= PetitPasInitialisation[i];
            }

            if (i < NbrMotorDynamixel)
            {
              Reference[i]->gotoa(ajout);
              delay(500);
            }
            /* else if (i >= NbrMotorDynamixel)
            {
              ReferenceStepper[i]->gotoa(ajout);
              delay(2000);
              //Je peut aussi set ca position actuelle comme je le veux
            } */
            readingstepper_fine = digitalRead(inPinsInterupteurNumber[i]);
          }

          ActualPosition[i] = ajout;
          ReferencePosition[i] = ajout;
          msg->getPayload()[i] = ReferencePosition[i];
          Serial.println("La nouvelle valeur du home position pour step =");
          Serial.println(Home[i]);
          delay(1000);
        }
      }

      //Go to HOME = 9
      else if (msg->getType() == GO_TO_HOME_INDEX)
      {
        ActualPosition[i] = msg->getPayload()[i];

        if (i < NbrMotorDynamixel)
        {
          if (reverseInitialisation[i] == 1)
          {
            Reference[i]->gotoa(ReferencePosition[i] - (Home[i]));
          }
          else
          {
            Reference[i]->gotoa(ReferencePosition[i] + Home[i]);
          }
          ActualPosition[i] = (Reference[i])->GetPosition1();
        }
        /* else if (i >= NbrMotorDynamixel)
        {
          ReferenceStepper[i]->gotoa(Home[i]);
          ActualPosition[i] = Home[i];
        } */
      }

      //Action on gripper = 24
      else if (msg->getType() == ACTION_ON_GRIPPER)
      {
        /* if (i < (NbrMotorDynamixel + NbrMotorStepper) && NbrMotorStepper != 0)
        {
          ReferenceStepper[i]->gotoa((msg->getPayload()[i]));
          ActualPosition[i] = (ReferenceStepper[i])->GetPosition1();
        } */
        if (i >= (NbrMotorDynamixel + NbrMotorStepper) && NbrMotorServo != 0)
        {
          float valeur = float((msg->getPayload()[i])) / 270 * 180;
          int valeur_int = valeur;
          (ReferenceServo[i])->gotoa(valeur_int);
          //ReferenceServo[i]->gotoa((msg->getPayload()[i]));
          Serial.println(valeur_int);
          ActualPosition[i] = msg->getPayload()[i];
          //ActualPosition[i] = (ReferenceServo[i])->GetPosition1();
        }
      }

      //CODE POUR RENVOYER LINFORMATION
      //CODE TO RETURN INFORMATION

      //return limites = 11
      else if (msg->getType() == RETURN_LIMITES_INDEX)
      {
        msg->getPayload()[i] = LimiteMax[i];
      }

      //return HOME position = 13
      else if (msg->getType() == RETURN_HOME_POSITION_INDEX)
      {
        msg->getPayload()[i] = Home[i];
      }

      //return reference position = 15
      else if (msg->getType() == RETURN_REFERENCE_POSITION_INDEX)
      {
        if (i < NbrMotorDynamixel)
        {
          //        Serial.println("Fonction not complete: Error");
          //        msg->getPayload()[i] = (Reference[i])->GetReferencePosition1();
          msg->getPayload()[i] = ReferencePosition[i];
        }
        else if (i >= NbrMotorDynamixel)
        {
          msg->getPayload()[i] = ReferencePosition[i];
        }
      }

      //return actual position = 17
      else if (msg->getType() == RETURN_ACTUAL_POSITION_INDEX)
      {
        if (i < NbrMotorDynamixel)
        {
          ActualPosition[i] = (Reference[i])->GetPosition1();
        }
        /* else if (i >= NbrMotorDynamixel)
        {
          ActualPosition[i] = (ReferenceStepper[i])->GetPosition1();
        } */
        msg->getPayload()[i] = ActualPosition[i];
      }
    }
    delay(1000);
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
#endif

/*
 * COMMANDE DE TESTFOR UNIT TEST
{​​"type":7,"PLS":1,"data":[19389]}​​
{​​"type":7,"PLS":1,"data":[19389]}​​
{​​"type":7,"PLS":3,"data":[10389,5000,0]}​​
{​​"type":11,"PLS":3,"data":[0,0,0]}​​
{​​"type":17,"PLS":3,"data":[0,0,0]}​​

{​​"type":17,"PLS":3,"data":[0,0,0]}​​

{​​"type":17,"PLS":2,"data":[0,0]}​​
{​​"type":3,"PLS":3,"data":[50,500,1500]}​​

{​​"type":5,"PLS":3,"data":[0,1,0]}​​
*/

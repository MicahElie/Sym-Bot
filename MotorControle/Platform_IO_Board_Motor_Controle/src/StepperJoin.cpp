#include <Arduino.h>
#include <ArduinoJson.h>

#include "StepperJoin.h"


StepperJoin::StepperJoin(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche, int MOTOR_IN1_PIN, int MOTOR_IN2_PIN, int MOTOR_IN3_PIN, int MOTOR_IN4_PIN) : Join(position, limite, homePosition, LimiteSwitchPinDroit, LimiteSwitchPinGauche) 
{
    stepmotor.connectToPins(MOTOR_IN1_PIN, MOTOR_IN2_PIN, MOTOR_IN3_PIN, MOTOR_IN4_PIN);
    stepmotor.setSpeedInStepsPerSecond(500);
    stepmotor.setAccelerationInStepsPerSecondPerSecond(1000);
}

StepperJoin::~StepperJoin()
{
    //stepmotor.disableMotor(); // check if it is necessary to put motor disable at the end?
}


void StepperJoin::goTo(int WantedPosition)
{
    int facteur_distance = 1;

    if (WantedPosition <= limite)
    {
        int nb_rotation =  facteur_distance * WantedPosition;
        stepmotor.moveToPositionInSteps(nb_rotation);// or stepmotor.moveToPositionInSteps(2048*nb_rotation);

        position = WantedPosition;
    }   
    else
    {
        position = -1;//Return error
    }
  
}


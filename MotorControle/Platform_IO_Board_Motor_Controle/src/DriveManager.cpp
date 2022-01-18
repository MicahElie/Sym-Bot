#include "DriveManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Arduino.h>

DriveManager::DriveManager()
{

}


DriveManager::~DriveManager()
{

}


void DriveManager::addJoin(Join* newJoin)
{
    Joins.add(newJoin);
}


void  DriveManager::deleteJointAt(int index)
 {
     Joins.remove(index);
 }


void DriveManager::goToHome()
{
    for (int i=0;i < Joins.size(); i++)
    {
        Joins.get(i)->goToHome();
    }
}


void DriveManager::goToPosition(Vector <int> position)
{
    for (int i=0;i < Joins.size();i++)
    {
        Joins.get(i)->goTo(position.get(i));
    }
}


void DriveManager::setHomePosition(Vector <int> newhomeposition)
{
    for (int i=0;i < Joins.size();i++)
    {
        Joins.get(i)->setHome(newhomeposition.get(i));       
    }
}

void DriveManager::calibrateAllJoin()
{
    //TODO:
    //function to calibrate the motors and define their parameters
    //A faire:
    //fonction pour calibrer les moteurs et definir leurs parametres
}

void DriveManager::goToPosition(int position[],int size)
{
    for (int i=0;i < size;i++)
    {
        Joins.get(i)->goTo(position[i]);
    }

}
#include "Join.h"

Join::Join(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche)
{
    this->position = position;
    this->limite = limite;
    this->homePosition = homePosition;
    this->LimiteSwitchPinDroit = LimiteSwitchPinDroit;
    this->LimiteSwitchPinGauche = LimiteSwitchPinGauche;    
}

Join::~Join()
{

}

void Join::goToHome()
{
    goTo(homePosition);
}

void Join::resetPosition()
{
    //goTo() : wait the bumper add  //attendre l'ajout des bumper
    position = 0;
}

int Join::getPosition()
{
    return position;
}

int Join::getLimite()
{
    return limite;
}

void Join::setLimite(int newLimite)
{
    limite = newLimite;
}

void Join::setHome(int newHomePosition)
{
    homePosition = newHomePosition;
}

int Join::getHome()
{
    return homePosition;
}
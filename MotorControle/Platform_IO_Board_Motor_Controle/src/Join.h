#ifndef JOIN_H
#define JOIN_H

class Join
{
    public:
        Join(int position, int limite, int homePosition, int LimiteSwitchPinDroit, int LimiteSwitchPinGauche);
        ~Join();

        virtual void goTo(int Wantedposition) = 0; 
        void goToHome();
        void resetPosition();
        int getPosition();
        int getLimite();
        void setLimite(int newLimite);
        void setHome(int newHomePosition);
        int getHome();

    protected:
        int position; 
        int limite;
        int homePosition;
        int LimiteSwitchPinDroit;
        int LimiteSwitchPinGauche;
        int Pin; // code pour indiquer les pins du arduino //code to indicate the arduino pins

};
#endif




#pragma once
#include "PowerUp.h"



class RandomPowerUp: public PowerUp{

    public:
        RandomPowerUp();
        bool powerOn(Player*);
        void activate(Player*);
        void keyPressed(int key, Player*);
        void render(Player*);
        void setCanActivate(bool);
    private:
        bool canActivate = false;

};
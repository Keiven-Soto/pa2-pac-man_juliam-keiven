#pragma once
#include "PowerUp.h"



class InvisiblePowerUp: public PowerUp{

    public:
        InvisiblePowerUp();
        void activate(Player*);
        void keyPressed(int key, Player*);
        void render(Player*);
        void setCanActivate(bool);
        void tick(Player*);
        bool powerOn(Player*);
    private:
        bool canActivate = false;
        int counter_to_stop = 0;
};
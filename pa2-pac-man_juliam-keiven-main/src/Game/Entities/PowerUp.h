#pragma once
#include "Player.h"

class PowerUp {//PowerUp class

    public:
        PowerUp() {}

        virtual void activate(Player*) = 0;
        bool powerOn();
        void keyPressed(int key);
        void deactivate();
        void conditions();
        bool isActive();
};
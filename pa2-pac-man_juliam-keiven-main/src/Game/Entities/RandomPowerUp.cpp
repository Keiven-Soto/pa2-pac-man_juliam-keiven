#include "RandomPowerUp.h"

RandomPowerUp::RandomPowerUp(){
}

void RandomPowerUp::activate(Player* player){//Activates power.
    player->randomPower();
}

void RandomPowerUp::keyPressed(int key, Player* player){
    if(key == ' '){//If spacebar is pressed, power is activated.
        if(player->getCollisionRG() && canActivate == true){
            activate(player);
            canActivate = false;
        }
    }
}

void RandomPowerUp::render(Player* player){//Makes the powerUp appear on screen.
    ofSetColor(124,252,0);
    if(player->getCollisionRG() && canActivate == true){
        ofDrawBitmapString("Random Place PowerUp",ofGetWidth()/2 - 490, 50);
    }
}

void RandomPowerUp::setCanActivate(bool b){//Setter for the condition if the powerup can be activated.
    canActivate = b;
}

bool RandomPowerUp::powerOn(Player* player){//This function tells you wether or not you have the power.
    if(player->getCollisionRG() && canActivate == true){
        return true;
    }else{return false;}
}
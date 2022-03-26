#include "InvisiblePowerUp.h"

InvisiblePowerUp::InvisiblePowerUp(){
}

void InvisiblePowerUp::activate(Player* player){//Activates power
    player->isInvisible(true);
}

void InvisiblePowerUp::keyPressed(int key, Player* player){
    if(key == ' '){//If spacebar is pressed, power is activated.
        if(player->getCollisionPG() && canActivate == true){
            activate(player);
            canActivate = false;
        }
    }

    if(key == 'k'){
        player->isInvisible(true); //Forces the player to turn invisible.
    }
}

void InvisiblePowerUp::tick(Player* player){ //Sets the time the player will remain invisible (aprox. 5s).
    if(player->getIsInvisible()){
        counter_to_stop ++;   
    }
    if(counter_to_stop == 125){
        player->isInvisible(false);
        counter_to_stop = 0;
    }
}

void InvisiblePowerUp::render(Player* player){ //Makes the powerUp appear on screen.
    ofSetColor(124,252,0);
    if(player->getCollisionPG() && canActivate == true){
        ofDrawBitmapString("Invisible PowerUp",ofGetWidth()/2 + 325, 50);
    }
}

void InvisiblePowerUp::setCanActivate(bool b){//Setter for the condition if the powerup can be activated.
    canActivate = b;
}

bool InvisiblePowerUp::powerOn(Player* player){//This function tells you wether or not you have the power.
    if(player->getCollisionPG() && canActivate == true){
        return true;
    }else{return false;}
}
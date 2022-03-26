#pragma once
#include "State.h"
#include "Player.h"
#include "MapBuilder.h"
#include "RandomPowerUp.h"
#include "InvisiblePowerUp.h"

class GameState: public State{
    public: 
        GameState();
        ~GameState();
        void resetPaused();
        void reset();
        void tick();
        void render();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void keyReleased(int key);
        int getFinalScore();
    
    private:
        ofSoundPlayer music;
        ofImage mapImage;
        Map* map;
        int finalScore=0;
        RandomPowerUp* random;
        InvisiblePowerUp* invisible;

};
#pragma once
#include "EntityManager.h"
#include "Animation.h"
#include "Ghost.h"
#include "Player.h"

class PeekABooGhost: public Ghost {
    public:
        PeekABooGhost(int, int, int, int, ofImage, EntityManager*, string,Player*);
        ~PeekABooGhost();
        void tick();
        string getColor();
        Player* getPlayer();
        ofImage getImage();
        void render();
        bool getKillable();
        void setKillable(bool);
    private:
        bool killable = false;
        FACING facing = UP;
        bool canMove = true;
        bool justSpawned=true;
        void checkCollisions();
        int speed=3;
        EntityManager* em;
        Animation* killableAnim;
        Player* player;
};
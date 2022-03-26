#pragma once

#include "EntityManager.h"
#include "Player.h"

class GhostSpawner: public Entity{
    public:
        GhostSpawner(int, int, int , int, EntityManager*, ofImage);
        void spawnRandomGhost(Player*,string);
        void spawnPeekABooGhost(Player*,string);
        void spawnGhost(string);
        void keyPressed(Player*,int);
        void tick(Player*);
    private:
        EntityManager* em;
        int count = 0;
        int spawnCounter = 30*5;
};
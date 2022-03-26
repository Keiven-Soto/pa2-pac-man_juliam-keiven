#pragma once
#include "Animation.h"
#include "EntityManager.h"



class Player: public Entity{

    private:
        int spawnX, spawnY;
        int health=3;
        int score=0;
        bool canMove;
        int speed = 8;
        bool walking = false;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;
        bool collisionRG = false;
        bool collisionPG = false;
        bool invisible = false;

    public:
        Player(int, int, int , int, EntityManager*);
        ~Player();
        int getHealth();
        float getX();
        float getY();
        int setX(int);
        int setY(int);
        void setHealth(int);
        int getScore();
        void setScore(int);
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void setFacing(FACING facing);
        void checkCollisions();
        void die();
        void randomPower();
        bool getCollisionRG();
        void setCollisionRG(bool);
        void isInvisible(bool);
        bool getIsInvisible();
        bool getCollisionPG();
        void setCollisionPG(bool);
        std::vector<Entity*> getEntities();
        
        
};

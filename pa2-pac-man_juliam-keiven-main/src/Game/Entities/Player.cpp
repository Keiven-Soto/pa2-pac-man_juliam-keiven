#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "RandomGhost.h"
#include "PeekABooGhost.h"

Player::Player(int x, int y, int width, int height, EntityManager* em) : Entity(x, y, width, height){
    spawnX = x;
    spawnY = y;
    sprite.load("images/pacman.png");
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    vector<ofImage> invisAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }

    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);
    this->em = em;
    
}

float Player::getX(){
    return x;
}
float Player::getY(){
    return y;
}

void Player::tick(){
    canMove = true;
    checkCollisions();
    if(canMove){
        if(facing == UP){
            y-= speed;
            if(!invisible){
                walkUp->tick();
            }
        }else if(facing == DOWN){
            y+=speed;
            if(!invisible){
                walkDown->tick();
            }
        }else if(facing == LEFT){
            x-=speed;
            if(!invisible){
                walkLeft->tick();
            }
        }else if(facing == RIGHT){
            x+=speed;
            if(!invisible){
                walkRight->tick();
            }
        }
    }
    
}

void Player::render(){
    ofSetColor(256,256,256);
    // ofDrawRectangle(getBounds());
    if(!invisible){ //If the player is invisble, it will not appear.
    if(facing == UP){
        walkUp->getCurrentFrame().draw(x, y, width, height);
        
    }else if(facing == DOWN){
        walkDown->getCurrentFrame().draw(x, y, width, height);
    }else if(facing == LEFT){
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    }else if(facing == RIGHT){
        walkRight->getCurrentFrame().draw(x, y, width, height);
        }
    }
    
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);
}

void Player::keyPressed(int key){
    switch(key){
        case 'w':
            setFacing(UP);
            break;
        case 's':
            setFacing(DOWN);
            break;
        case 'a':
            setFacing(LEFT);
            break;
        case 'd':
            setFacing(RIGHT);
            break;
        case 'n':
            die();
            break;
        case 'm':
            if(health < 3){health++;}//Limits lives to 3.
            break;
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

void Player::setFacing(FACING facing){
    this->facing = facing;
}

int Player::getHealth(){
    return health;
}

void Player::setHealth(int h){
    health = h;
}
int Player::getScore(){
    return score;
}

void Player::setScore(int h){
    score = h;
}
void Player::setCollisionRG(bool b){//boolean setter if collides with an instance of RegularGhost.
    collisionRG = b;
}
bool Player::getCollisionRG(){//boolean getter if collides with an instance of RandomGhost.
    return collisionRG;
}
void Player::randomPower(){//Makes player teleport to a random dot.
    Entity* replacement_dot = em->entities[ofRandom(em->entities.size())];//Picks a random dot.
    float randomX = replacement_dot->getX();//Position of random dot.
    float randomY = replacement_dot->getY();

    em->entities.erase(std::remove(em->entities.begin(),em->entities.end(),replacement_dot),em->entities.end());//Eliminates from existance random dot.
    x = randomX;//Teleports player to the position of the random dot.
    y = randomY;
}

void Player::setCollisionPG(bool b){//boolean setter if collides with an instance of PeekABooGhost.
    collisionPG = b;
}

bool Player::getCollisionPG(){//boolean getter if collides with an instance of PeekABooGhost.
    return collisionPG;
}

void Player::isInvisible(bool b){//boolean setter if the player turns invisible.
    invisible = b;
} 
bool Player::getIsInvisible(){//boolean getter if the player turns invisible.
    return invisible;
}

void Player::checkCollisions(){
    for(BoundBlock* BoundBlock: em->BoundBlocks){
        switch(facing){
            case UP:
                if(this->getBounds(x, y-speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case DOWN:
                if(this->getBounds(x, y+speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case LEFT:
                if(this->getBounds(x-speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case RIGHT:
                if(this->getBounds(x+speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
        }
    }
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                entity->remove = true;
                score += 10;
            }
            if(dynamic_cast<BigDot*>(entity)){
                score +=10;
                em->setKillable(true);
            }
        }
    }
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if(ghost->getKillable()){
                ghost->remove = true;
            }else{
                if(!invisible){die();}//Is not affected by ghosts if invisible.
                }
            }
    }
        // the following 2 for loops make all instances of  
        // randomGhost and PeekABooGhost do the same as a regular ghost.
    for(Entity* entity:em->randomGhost){
        if(collides(entity)){
            RandomGhost* random_ghost = dynamic_cast<RandomGhost*>(entity);
            if(random_ghost->getKillable()){
                setCollisionRG(true);//sets collision with RandomGhost true.
                random_ghost->remove = true;
            }else{
                if(!invisible){die();}
                }

            }
        }
        for(Entity* entity:em->peekabooGhost){
        if(collides(entity)){
            PeekABooGhost* peekaboo_ghost = dynamic_cast<PeekABooGhost*>(entity);
            if(peekaboo_ghost->getKillable()){
                setCollisionPG(true);//sets collision with PeekABooGhost true.
                peekaboo_ghost->remove = true;
            }else{
                if(!invisible){die();}
                }

            }
        }

    
}

void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}

Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}

std::vector<Entity*> Player::getEntities(){
    return em->entities;
}
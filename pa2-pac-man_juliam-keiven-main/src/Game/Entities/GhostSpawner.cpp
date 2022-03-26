#include "GhostSpawner.h"
#include "Ghost.h"
#include "RandomGhost.h"
#include "PeekABooGhost.h"
#include <algorithm>

GhostSpawner::GhostSpawner(int x, int y, int width, int height, EntityManager* em, ofImage sprite) : Entity(x, y, width, height){
    this->em = em;
    this->sprite = sprite;
    spawnGhost("red");
    spawnGhost("pink");
    spawnGhost("cyan");
    spawnGhost("orange");

}

void GhostSpawner::tick(Player* player){
    std::vector<string> colors;
    colors.push_back("red");
    colors.push_back("pink");
    colors.push_back("cyan");
    colors.push_back("orange");

    if(em->ghosts.size()<4){
        if(spawnCounter == 0){
            spawnGhost(colors[ofRandom(4)]);
            spawnCounter = 30*5;
        }else{
            spawnCounter--;
        }
    }
    if(player->getScore() == 500){// If the score is 500, RandomGhost spawns.
        while(count == 0){
            spawnRandomGhost(player,colors[ofRandom(4)]);
            count ++;
            }
        }
    if(player->getScore() >= 500 && em->randomGhost.size() == 0){ //This is to spawn a RandomGhost if the previous one was eaten.
        count = 0;
        while(count == 0){
            spawnRandomGhost(player,colors[ofRandom(4)]);
            count ++;
        }
    } 
    if(player->getScore() == 1000 && em->peekabooGhost.size() == 0){ // If the score is 1000, PeekABooGhost spawns.
        count = 0;
        while(count == 0){
            spawnPeekABooGhost(player,colors[ofRandom(4)]);
            count ++;
        }
    }  
}
void GhostSpawner::spawnGhost(string color){
    Ghost* g = new Ghost(x,y,width-2,height-2,sprite,em, color);
    em->ghosts.push_back(g);
}

// This function is what makes an instance of PeekABooGhost spawn.
void GhostSpawner::spawnPeekABooGhost(Player* player,string color){
    PeekABooGhost* p = new PeekABooGhost(x,y,width-2,height-2,sprite,em, color, player);
    em->peekabooGhost.push_back(p);
}

// This function is what makes an instance of RandomGhost spawn.
void GhostSpawner::spawnRandomGhost(Player* player, string color){
    float playerX = player->getX(); //gets the player's position.
    float playerY = player->getY();
    count = 0; //counter to break loop.
    int count_to_break = 0; //counter to break loop if condition never appears.
    int distance = 120; //distance set (x amount of pixels)
    while(count == 0){
        Entity* replacement_dot = em->entities[ofRandom(em->entities.size())]; // Finds a dot to replace.

        count_to_break++;
        if(count_to_break > em->entities.size()){count++;} // Means that there are no more dots to find, so condition will not happen.

        float randomX = replacement_dot->getX(); // Gets the random dot's position.
        float randomY = replacement_dot->getY();

        // The following formula determines wether or not the dot is too close to the player.
        if((randomX - distance > playerX || randomX + distance < playerX)||(randomY - distance > playerY || randomY + distance < playerY)){
            em->entities.erase(std::remove(em->entities.begin(),em->entities.end(),replacement_dot),em->entities.end()); // Erases random dot from existance.

            RandomGhost* r = new RandomGhost(randomX,randomY,width-2,height-2,sprite,em,color); // Spawns a ghost in place of the random dot.
            em->randomGhost.push_back(r);
            count++; //To break loop.
        }
    }
    
}

void GhostSpawner::keyPressed(Player* player,int key){
        std::vector<string> colors;
        colors.push_back("red");
        colors.push_back("pink");
        colors.push_back("cyan");
        colors.push_back("orange");
    if(key == 'g'){ //To force spawn an instance of ghost.
        spawnGhost(colors[ofRandom(4)]); 
    }
    if(key == 'r'){
        spawnRandomGhost(player,colors[ofRandom(4)]); //To force spawn an instance of RandomGhost.
    }
    if(key == 'b'){
        spawnPeekABooGhost(player,colors[ofRandom(4)]); //To force spawn an instance of PeekABooGhost.
    }
}
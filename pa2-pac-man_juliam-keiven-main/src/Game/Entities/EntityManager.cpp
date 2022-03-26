#include "EntityManager.h"
#include "Ghost.h"
#include "RandomGhost.h"
#include "PeekABooGhost.h"

void EntityManager::tick(){
    if(killable){
        killableCounter--;
        if (killableCounter == 0){
            killable = false;
            for(Entity* entity:ghosts){
                Ghost* ghost = dynamic_cast<Ghost*>(entity); 
                ghost->setKillable(false);
            }
            // the following 2 for loops make all instances of
            // randomGhost and PeekABooGhost do the same as a regular ghost.
            for(Entity* entity:randomGhost){
                RandomGhost* random_ghost = dynamic_cast<RandomGhost*>(entity);
                random_ghost->setKillable(false);
            }
            for(Entity* entity:peekabooGhost){
                PeekABooGhost* peekaboo_ghost = dynamic_cast<PeekABooGhost*>(entity);
                peekaboo_ghost->setKillable(false);
            }
        }
    }
    std::vector<int> toRemove;

    for(int i=0;i<entities.size();i++){
        if(!entities[i]->remove){
            entities[i]->tick();

        }else{
            toRemove.push_back(i);
        }
    }
    for(unsigned int removable: toRemove){
        Entity* entityPointer = *(entities.begin() + removable);
        entities.erase(entities.begin() + removable);
        delete entityPointer;
    }
    toRemove.clear();
    for(BoundBlock* BoundBlock: BoundBlocks){
        BoundBlock->tick();
    }
    for(int i=0;i<ghosts.size();i++){
        if(!ghosts[i]->remove){
            ghosts[i]->tick();

        }else{
            toRemove.push_back(i);
        }
    }       // the following 4 for loops make all instances of
            // randomGhost and PeekABooGhost do the same as a regular ghost.
    for(unsigned int removable: toRemove){
        Ghost* entityPointer = dynamic_cast<Ghost*>(*(ghosts.begin() + removable));
        ghosts.erase(ghosts.begin() + removable);
        delete entityPointer;
    }
    toRemove.clear();
    for(int i=0;i<randomGhost.size();i++){
        if(!randomGhost[i]->remove){
            randomGhost[i]->tick();
        }else{
            toRemove.push_back(i);
        }
    }
    for(unsigned int removable: toRemove){
        RandomGhost* entityPointer = dynamic_cast<RandomGhost*>(*(randomGhost.begin() + removable));
        randomGhost.erase(randomGhost.begin() + removable);
        delete entityPointer;
    }
    toRemove.clear();
    for(int i=0;i<peekabooGhost.size();i++){
        if(!peekabooGhost[i]->remove){
            peekabooGhost[i]->tick();
        }else{
            toRemove.push_back(i);
        }
    }
    
    for(unsigned int removable: toRemove){
        PeekABooGhost* entityPointer = dynamic_cast<PeekABooGhost*>(*(peekabooGhost.begin() + removable));
        peekabooGhost.erase(peekabooGhost.begin() + removable);
        delete entityPointer;
    }
    toRemove.clear();
}   
    

void EntityManager::render(){
    for(Entity* entity: entities){
        entity->render();
    }   // the following 2 for loops make all instances of
        // randomGhost and PeekABooGhost do the same as a regular ghost.
    for(Entity* random_ghost: randomGhost){
        random_ghost->render();
    }
    for(Entity* peekaboo_ghost: peekabooGhost){
        peekaboo_ghost->render();
    }
    for(BoundBlock* BoundBlock: BoundBlocks){
        BoundBlock->render();
    }
    for(Entity* ghost: ghosts){
        ghost->render();
    }
}

void EntityManager::setKillable(bool k){
    killable = true;
    killableCounter=30*10;
    for(Entity* entity:ghosts){
        Ghost* ghost = dynamic_cast<Ghost*>(entity); 
        ghost->setKillable(true);
    }   // the following 2 for loops make all instances of
        // randomGhost and PeekABooGhost do the same as a regular ghost.
    for(Entity* entity:randomGhost){
        RandomGhost* random_ghost = dynamic_cast<RandomGhost*>(entity); 
        random_ghost->setKillable(true);
    }
    for(Entity* entity:peekabooGhost){
        PeekABooGhost* peekaboo_ghost = dynamic_cast<PeekABooGhost*>(entity); 
        peekaboo_ghost->setKillable(true);
    }
}

EntityManager::~EntityManager(){
    for(Entity* e: BoundBlocks){
        delete e;

    }
    for(Entity* e: ghosts){
        Ghost* ghostPointer = dynamic_cast<Ghost*>(e);
        delete e;
    }
    for(Entity* e: entities){
        delete e;
    }
    BoundBlocks.clear();
    ghosts.clear();
    entities.clear();
}


#include "GameState.h"
#include "Entity.h"

GameState::GameState() {
    music.load("music/pacman_chomp.wav");
    mapImage.load("images/map1.png");
    map = MapBuilder().createMap(mapImage);
    random = new RandomPowerUp();//Creates a new instance of RandomPowerUp.
    invisible = new InvisiblePowerUp();//Creates a new instance of InvisiblePowerUp.
}
void GameState::tick() {
    if(!music.isPlaying()){
            music.play();
    }
    invisible->tick(map->getPlayer());
    map->tick();
	if(map->getPlayer()->getScore() == 500){//makes powers set ready to be activated when colliding with respective ghosts.
		random->setCanActivate(true);
		invisible->setCanActivate(true);
	}
    finalScore = map->getPlayer()->getScore();//Updates score.
    if(map->getPlayer()->getHealth() == 0){
        setFinished(true);
        setNextState("over");//sets next stage to over.
        map->getPlayer()->setHealth(3);
        map->getPlayer()->setScore(0);
    }

    if(map->getPlayer()->getEntities().size() == 0){
        setFinished(true);
        setNextState("Win");
        map->getPlayer()->setHealth(3);
        map->getPlayer()->setScore(0);    
    }
}
void GameState::render() {
    map->render();
    random->render(map->getPlayer());
    invisible->render(map->getPlayer());
}

void GameState::keyPressed(int key){
    map->keyPressed(key);
    if(invisible->powerOn(map->getPlayer()) && random->powerOn(map->getPlayer())){invisible->keyPressed(key,map->getPlayer());}
    else{
        random->keyPressed(key,map->getPlayer());
        invisible->keyPressed(key,map->getPlayer());
    }
}

void GameState::mousePressed(int x, int y, int button){
    map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
    map->keyReleased(key);
}
void GameState::resetPaused(){//reset that not makes a new instance of map.
    setFinished(false);
    setNextState("");    
}

void GameState::reset(){//reset that makes a new instance of map.
    setFinished(false);
    setNextState("");
    map = MapBuilder().createMap(mapImage);
}

int GameState::getFinalScore(){
    return finalScore;
}

GameState::~GameState(){
    delete map;
}
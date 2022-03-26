#include "PausedState.h"

PausedState::PausedState() {
	resume = new Button(ofGetWidth()/2-20, ofGetHeight()/2, 64, 50, "Resume");//New resume button.
    quit = new Button(ofGetWidth()/2+50, ofGetHeight()/2, 64, 50, "Quit");//new quit button
	img1.load("images/Pause.png");//Paused image.

}

void PausedState::resetPaused(){

}

void PausedState::tick() {
	resume->tick();
    quit->tick();
    if(quit->wasPressed()){//If the quit button is pressed, the next stage is set to Over.
		setNextState("over");
		setFinished(true);
		setPaused(false);

    }
	if(resume->wasPressed()){//If the resume button is pressed, the next stage is set to Game.
		setNextState("Game");
		setFinished(true);
		setPaused(true);
		

	}
}
void PausedState::render() {
    ofDrawBitmapString("Game has been Paused.", ofGetWidth()/2, ofGetHeight()/2-200, 50);//Makes those letters appear.
	ofDrawBitmapString("Score: " + to_string(score), ofGetWidth()/2, ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	img1.draw(ofGetWidth()/2, ofGetHeight()/2-100, 100, 100);//Makes paused image appear.
	resume->render();//Makes the buttons appear.
    quit->render();


}

void PausedState::keyPressed(int key){
	
}

void PausedState::mousePressed(int x, int y, int button){
	resume->mousePressed(x, y);
    quit->mousePressed(x,y);
}

void PausedState::reset(){
	setFinished(false);
	setNextState("");
	resume->reset();//Resets buttons.
    quit->reset();
}

void PausedState::setScore(int sc){
    score = sc;
}

PausedState::~PausedState(){
	delete resume;
    delete quit;
}
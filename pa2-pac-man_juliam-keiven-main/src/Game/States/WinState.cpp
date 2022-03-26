#include "WinState.h"

WinState::WinState() {
	playAgainButton = new Button(ofGetWidth()/2-20, ofGetHeight()/2, 64, 50, "Play Again!");//New play again Button.
	img1.load("images/Trophy_animated.png");//Image of trophy

}
void WinState::tick() {
	playAgainButton->tick();
	if(playAgainButton->wasPressed()){//If the play again button is pressed, the next stage is set to game. 
		setNextState("Game");
		setFinished(true);
		setPaused(false);

	}
}
void WinState::render() {
    ofDrawBitmapString("YOU WON!", ofGetWidth()/2, ofGetHeight()/2-200, 50);//Makes those letters appear on screen.
	ofDrawBitmapString("Score: " + to_string(score), ofGetWidth()/2, ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	img1.draw(ofGetWidth()/2, ofGetHeight()/2-100, 100, 100);//Makes the trophy appear.
	playAgainButton->render();


}

void WinState::keyPressed(int key){
	
}

void WinState::mousePressed(int x, int y, int button){
	playAgainButton->mousePressed(x, y);
}

void WinState::reset(){
	setFinished(false);
	setNextState("");
	playAgainButton->reset();
}

void WinState::setScore(int sc){
    score = sc;
}

WinState::~WinState(){
	delete playAgainButton;
}

void WinState::resetPaused(){

}
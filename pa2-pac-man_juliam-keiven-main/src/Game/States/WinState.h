#pragma once

#include "State.h"
#include "Button.h"
#include "Animation.h" 

class WinState: public State{
private:
	ofImage img1;
	Button *playAgainButton;
	int score = 0;
public:
	WinState();
	~WinState();
	void resetPaused();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
	void setScore(int);
};

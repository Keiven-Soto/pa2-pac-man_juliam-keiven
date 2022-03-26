#pragma once

#include "State.h"
#include "Button.h"
#include "Animation.h" 

class PausedState: public State{
private:
	ofImage img1;
	Button *resume;
    Button *quit;
	int score = 0;
	
public:
	PausedState();
	~PausedState();
	void resetPaused();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
	void setScore(int);
};
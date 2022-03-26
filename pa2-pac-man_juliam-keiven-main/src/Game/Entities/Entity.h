#pragma once
#include "ofMain.h"

enum FACING {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Entity {
	protected:
		int x, y, width, height, health;
		ofImage sprite;
		int ticks = 0;
	public:
		explicit Entity(int x, int y, int width, int height);
		virtual void tick();
		virtual void render();
		float getX();
		float getY();
		bool remove = false;
		void damage(Entity* damageSource);
		bool collides(Entity* entity);
		ofRectangle getBounds();
		ofRectangle getBounds(int x, int y);
};
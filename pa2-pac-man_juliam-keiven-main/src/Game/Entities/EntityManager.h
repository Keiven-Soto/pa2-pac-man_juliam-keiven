#pragma once

#include "BoundBlock.h"


class EntityManager {

public:
	~EntityManager();
	std::vector<Entity*> entities;
	std::vector<BoundBlock*> BoundBlocks;
	std::vector<Entity*> ghosts;
	std::vector<Entity*> randomGhost;
	std::vector<Entity*> peekabooGhost;
	void tick();
	void render();
	void setKillable(bool);

private:
	bool killable = false;
	int killableCounter;
};
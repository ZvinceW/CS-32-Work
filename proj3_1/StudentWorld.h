#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Field.h"
#include <string>
#include <vector>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
//for pt1, finish: init(), move(), cleanup(), destructor?

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{

	}

	bool isPebble(int x, int y);

	virtual int init();

	virtual int move();

	virtual void cleanUp();

	virtual ~StudentWorld();

private:
	int ticks;
	std::vector<Actor*> m_actorMap[VIEW_HEIGHT][VIEW_WIDTH]; //2d vector represent the entire map, each cell holds a vector of actors that represent the actors in that cell
};

#endif // STUDENTWORLD_H_

#include "StudentWorld.h"
#include <string>
#include <list>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

bool StudentWorld::isPebble(int x, int y)
{
	bool result = false;
	for (unsigned int i = 0; i < m_actorMap[y][x].size(); i++)
	{
		if (m_actorMap[y][x][i]->canBlock())
		{
			result = true;
		}
	}
	return result;
}

int StudentWorld::init()
{
	ticks = 0;
	string fieldFileName; Field f;
	std::string fieldFile = getFieldFilename();
	//std::string fieldFile = "field.txt";
	if (f.loadField(fieldFile) != Field::LoadResult::load_success) 
	{ 
		return false;  //make sure the field loads correctly
	}

	//adding babyGrass and pebble into actorMap
	for (int i = 0; i < VIEW_HEIGHT; i++)
	{
		for (int j = 0; j < VIEW_WIDTH; j++)
		{

			Field::FieldItem item = f.getContentsOf(j, i); //do (j, i) because the field uses (x, y) while the 2d vector uses (y, x)
			//dynamically allocating the actor objects
			switch (item) {
			case Field::grasshopper:
				m_actorMap[i][j].push_back(new babyGrasshopper(j, i, this)); //flipped to (y, x)
				break;
			case Field::rock:
				m_actorMap[i][j].push_back(new pebble(j, i));  //flipped to (y, x)
				break;
			}
		}
	}

	//this should be done now, pebble and babyGrass all in actorMap
	
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	// This code is here merely to allow the game to build, run, and terminate after you hit enter.
	// Notice that the return value GWSTATUS_NO_WINNER will cause our framework to end the simulation.
	ticks++;
	for (int i = 0; i < VIEW_HEIGHT; i++)
	{
		for (int j = 0; j < VIEW_WIDTH; j++)
		{
			for (unsigned int k = 0; k < m_actorMap[i][j].size(); k++)
			{
				//record current actor location
				int tempX = m_actorMap[i][j][k]->getX();
				int tempY = m_actorMap[i][j][k]->getY();
				//make the actor do sth if the actor is not dead and it hasnt been moved already
				if (!(m_actorMap[i][j][k]->isDEAD()) && !(m_actorMap[i][j][k]->isChecked()))
				{
					m_actorMap[i][j][k]->doSomething();
				}
				//make the checker true upon making the actor move, so it doesnt get checked again
				m_actorMap[i][j][k]->setCheck(true);
				//record new location
				int newX = m_actorMap[i][j][k]->getX();
				int newY = m_actorMap[i][j][k]->getY();
				//check if the coordinates have changed since the actor's action
				if (newX != tempX || newY != tempY)
				{
					//if so, move the actor to the new corresponding position in actorMap
					//sending to new location
					m_actorMap[newY][newX].push_back(m_actorMap[i][j][k]); 
					//erasing the original from its original location in actorMap
					m_actorMap[i][j].erase(m_actorMap[i][j].begin() + k); 
				}
			}
		}
	}
	
	//this loop deletes all the dead actor and replace with food
	for (int i = 0; i < VIEW_HEIGHT; i++)
	{
		for (int j = 0; j < VIEW_WIDTH; j++)
		{
			for (unsigned int k = 0; k < m_actorMap[i][j].size(); k++)
			{
				m_actorMap[i][j][k]->setCheck(false); //so the actor can still be processed next tick
				if (m_actorMap[i][j][k]->isDEAD())
				{
					delete m_actorMap[i][j][k]; //disallocate the dead actor
					m_actorMap[i][j].erase(m_actorMap[i][j].begin() + k); //erase the deleted pointer
					k--; //so we dont skip over an element
					m_actorMap[i][j].push_back(new food(j, i, this)); //place down food at same location
				}
			}
		}
	}

	//update tick count
	setGameStatText("Ticks: " + to_string(ticks));

	if (ticks >= 2000)
	{
		/*
		if (weHaveAWinningAnt()) {
			setWinner(getWinningAntsName()); return GWSTATUS_Ant_WON;
		}
		else
		*/
		return GWSTATUS_NO_WINNER;
	}

	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	for (int i = 0; i < VIEW_HEIGHT; i++)
	{
		for (int j = 0; j < VIEW_WIDTH; j++)
		{
			for (unsigned int k = 0; k < m_actorMap[i][j].size(); k++)
			{
				delete m_actorMap[i][j][k];
			}
		}
	}
}

StudentWorld::~StudentWorld()
{
	//cleanUp();
}

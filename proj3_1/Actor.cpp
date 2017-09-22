#include "Actor.h"
#include "StudentWorld.h"
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int ID, int x, int y, Direction dir, int depth) : 
	GraphObject(ID, x, y, dir, depth)
{
	isDead = false;
}

bool Actor::isDEAD() const
{
	return isDead;
}

void Actor::setDead(bool b)
{
	isDead = b;
}

bool Actor::isChecked() const
{
	return checked;  //see if the actor has already done sth during that tick
}

void Actor::setCheck(bool b)
{
	checked = b;  //used to set/reset the checker
}

bool Actor::canBlock() const
{
	return false;   //most actors cant block bugs and stuff
}

energyHolder::energyHolder(int ID, int x, int y, int energy, StudentWorld* arena, Direction dir, int depth) :
	Actor(ID, x, y, dir, depth)
{
	m_energyLvl = energy; //set initial energy level
	m_arena = arena; //store its copy of StudentWorld
}

void energyHolder::doSomething()
{
	m_energyLvl--; //lose 1 unit every tick
	if (m_energyLvl <= 0) //dead when no energy
	{
		setDead(true);
	}
}

StudentWorld * energyHolder::getArena() const
{
	return m_arena;
}

void energyHolder::gain(int amount)
{
	m_energyLvl += amount;
}

void energyHolder::lose(int amount)
{
	m_energyLvl -= amount;
	if (m_energyLvl <= 0) //stuff is gone after energyLvl depletes
	{
		setDead(true);
	}
}

int energyHolder::getEnergy() const
{
	return m_energyLvl;
}

food::food(int x, int y, StudentWorld* arena) :
	energyHolder(IID_FOOD, x, y, 6000, arena, right, 2) {}

void food::doSomething() {}



bug::bug(int ID, int x, int y, int energy, StudentWorld* arena, Direction dir, int depth) :
	energyHolder(ID, x, y, energy, arena, dir, depth)
{
	int result = randInt(1, 4);
	switch (result) //random starting direction
	{
	case 1:
		setDirection(left);
		break;
	case 2:
		setDirection(right);
		break;
	case 3:
		setDirection(up);
		break;
	case 4:
		setDirection(down);
		break;
	default:
		break;
	}
	m_stunned = false; //not stunned
	m_blocked = false; //not blocked
	//m_foodHeld = 0;    //not holding food
}


void bug::setStun(bool b)
{
	m_stunned = b;
}

void bug::setBlock(bool b)
{
	m_blocked = b;
}

void bug::setStunRound(int i)
{
	m_roundStunned = i;
}

int bug::getStunRound() const
{
	return m_roundStunned;
}

bool bug::checkStun()
{
	return m_stunned;
}

bool bug::checkBlock()
{
	return m_blocked;
}

void bug::eat(food fd)
{

}

int bug::getDistance() const
{
	return m_distance;
}

void bug::setDistance(int distance)
{
	m_distance = distance;
}

pebble::pebble(int x, int y) :
	Actor(IID_ROCK, x, y) {}

bool pebble::canBlock() const
{
	return true;  //pebble will block stuff
}

void pebble::doSomething()
{
	//pebble doesnt do anything
}

babyGrasshopper::babyGrasshopper(int x, int y, StudentWorld* arena):
	bug(IID_BABY_GRASSHOPPER, x, y, 500, arena)
{
	//bug constructor already picked a random direction for us
	int initDist = randInt(2, 10); //set initial distance to a random int: [2, 10]
	setDistance(initDist);
	//finish studentworld before coming back again
}

void babyGrasshopper::doSomething()
{
	lose(1); //lose 1 hp per tick
	if (getEnergy() <= 0)
	{
		setDead(true);
		return;
	}
	else if (getStunRound() > 0) //dont do stuff if there're remaining stun rounds
	{
		setStunRound(getStunRound() - 1); //decrement that stun round
		return;
	}
	else //do stuff
	{
		/*
		//moult into adult
		if(getEnergy() >= 1660)
		{
			//MOULT
		}

		//eat dat food
		if(theresFoodInCell())
		{
			//attempt to eat 200 food
			//50% chance of going back to sleep
		}
		*/
		//if done moving in the current direction
		if (getDistance() == 0)
		{
			//set random direction
			int result = randInt(1, 4);
			switch (result) 
			{
			case 1:
				setDirection(left);
				break;
			case 2:
				setDirection(right);
				break;
			case 3:
				setDirection(up);
				break;
			case 4:
				setDirection(down);
				break;
			default:
				break;
			}
			//set random distance
			int Dist = randInt(2, 10); //set initial distance to a random int: [2, 10]
			setDistance(Dist);
		}
		//move one space toward the current direction
		if (getDirection() == left) {
			if (!(getArena()->isPebble(getX() - 1, getY()))) //move to the target space if its not occupied by a pebble
			{
				moveTo(getX() - 1, getY());
				setDistance(getDistance() - 1); //decrease the distance toward that direction by 1
			}
			else //if the target space IS occupied by pebble
			{
				setDistance(0); //set the distance toward that direction to zero, so it will pick a new direction next tick
			}
		}
		else if (getDirection() == right) {
			if (!(getArena()->isPebble(getX() + 1, getY())))
			{
				moveTo(getX() + 1, getY());
				setDistance(getDistance() - 1);
			}
			else
			{
				setDistance(0);
			}
		}
		else if (getDirection() == up) {
			if (!(getArena()->isPebble(getX(), getY() + 1)))
			{
				moveTo(getX(), getY() + 1);
				setDistance(getDistance() - 1);
			}
			else
			{
				setDistance(0);
			}
		}
		else {
			if (!(getArena()->isPebble(getX(), getY() - 1)))
			{
				moveTo(getX(), getY() - 1);
				setDistance(getDistance() - 1);
			}
			else
			{
				setDistance(0);
			}
		}

		//set # of ticks to sleep to 2
		setStunRound(2);
	}
}


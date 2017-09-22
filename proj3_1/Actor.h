#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject
{
public:
	Actor(int ID, int x, int y, Direction dir = right, int depth = 1);
	virtual void doSomething() = 0;
	bool isDEAD() const;
	void setDead(bool b);
	bool isChecked() const;
	void setCheck(bool b);
	virtual bool canBlock() const;
private:
	bool isDead;
	bool checked = false;
};

class pebble : public Actor
{
public:
	pebble(int x, int y);
	virtual bool canBlock() const;
	virtual void doSomething();
};

class energyHolder : public Actor
{
public:
	energyHolder(int ID, int x, int y, int energy, StudentWorld* arena, Direction dir = right, int depth = 1);
	virtual void doSomething();
	StudentWorld* getArena() const;
	void gain(int amount);
	void lose(int amount);
	int getEnergy() const;
private:
	int m_energyLvl;
	StudentWorld* m_arena;
};

class food : public energyHolder
{
public:
	food(int x, int y, StudentWorld* arena);
	void doSomething();
	//int eat(int amount);

};

class bug : public energyHolder
{
public:
	bug(int ID, int x, int y, int energy, StudentWorld* arena, Direction dir = right, int depth = 1);
	//virtual void doSomething();
	void setStun(bool b);
	void setBlock(bool b);
	void setStunRound(int i);
	int getStunRound() const;
	bool checkStun();
	bool checkBlock();
	void eat(food fd);
	int getDistance() const;
	void setDistance(int distance);
private:
	//int m_foodHeld;
	int m_roundStunned = 2;
	int m_distance;
	bool m_blocked;
	bool m_stunned;
};

class babyGrasshopper : public bug
{
public:
	babyGrasshopper(int x, int y, StudentWorld* arena);
	virtual void doSomething();
};

#endif // ACTOR_H_

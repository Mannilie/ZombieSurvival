////////////////////////////////////////////////////////////
// File: ZombieSpawner.h
// Author: Emmanuel Vaccaro
// Date: 23/03/2014
// Brief: Manages the zombie spawns and some zombie mathematics
////////////////////////////////////////////////////////////
#ifndef __ZOMBIESPAWNER_H__
#define __ZOMBIESPAWNER_H__

#include "GameObject.h"
#include "Zombie.h"
#include "Player.h"
#include "ZombieBox.h"

class ZombieSpawner : public GameObject
{
private:
	Point2D oRandZombieSpawn;	//Point2D used for obtaining the random spawn locations on the map
	int m_iRandomZombieSpawn;	//Used to store the random switch statement's number
	float m_fRandX, m_fRandY;	//Used to store the random locations to be passed as a float
	char m_cZombiesKilled[64];	//Stores the converted amount of zombies killed from itoa
	int m_iZombiesKilled;		//Stores the amount of zombies killed
	float m_fZombieSpeed;		//Stores the zombie's speed as a float
	int m_iZombieAmount;		//Stores the zombie's amount
	int m_iMapDimension;		//Stores the map's dimension
	int m_iRandomBlood;			//Stores the random blood number
	Zombie** m_oZombie;			//Creates a zombie double pointer
public:
	ZombieSpawner();	//Default constructor
	~ZombieSpawner();	//Default deconstructor
	void UpdateZombies(Player* m_oPlayer);	//Updates zombies
	int CurrentZombiesKilled();	//int function returns the current zombies killed
	Zombie** ReturnZombie();	//Zombie pointer array function returns the zombie pointer array
	void ZombieKilled();		//void function gets the amount of zombies killed
	void DrawZombies();			//Draws all zombies
	void InitialiseZombies();	//Initialises all the zombies
};

#endif //__ZOMBIESPAWNER_H__
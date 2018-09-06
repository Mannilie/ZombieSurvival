////////////////////////////////////////////////////////////
// File: Zombie.h
// Author: Emmanuel Vaccaro
// Date: 23/03/2014
// Brief: Manages the zombie game object and zombie mathematics
////////////////////////////////////////////////////////////
#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include "GameObject.h"
#include "ZombieBox.h"
#include "Player.h"
#include "Textures.h"
#include <math.h>
#include <stdlib.h>
#include "ZombieBox.h"

class Zombie : public GameObject, public Textures
{
protected:
	int m_iZombieAliveTimer;	//Used as a timer to count down until the zombie is set to non-existent
	int m_iShowHealthTimer;		//Used as a timer to count how long the zombie's health is shown for
	bool m_bZombieKilled;		//Used to check if the zombie has been killed by the player
	float m_fZombieSpeed;		//Used to store the zombie's speed
	float m_fZombieAngle;		//Used to store the zombie's angle calculated relative to the player's position		
	int m_iZombieHealth;		//Used to store the zombie's health
	char m_cHealth[64];			//Used to store the converted health from an int to a char to be displayed on screen
	bool m_bShowHealth;			//Used to check whether to show health or not
	bool m_bBloodShown;			//Used to check whether or not the blood is showing
	int m_iDamage;				//Stores the zombie's damage toward the player
	bool m_bAlive;				//Used to check if the zombie is alive
	float a_dPI;
	ZombieBox* m_oZombieBox;
public:
	Zombie();	//Default constructor
	~Zombie();	//Default deconstructor
	Zombie(bool a_bAlive, int a_iWidth, int a_iHeight, Point2D a_oPosition, float a_oZombieSpeed, int a_iRandomBlood);	//Custom constructor
	void Update(float a_oPlayerPositionX, float a_oPlayerPositionY, Player* a_oPlayer);	//Update function
	void DeployZombie(float a_oPlayerPositionX, float a_oPlayerPositionY);	//void function used to spawn the zombie in a given location
	void Draw();	//Draws the zombie
	void ZombieHit(int a_iBulletDamage);	//void function handles the event when the zombie is hit by a bullet
	Point2D GetZombiePos();	//Point2D returns the location of the zombie
	bool GetZombieKilled();	//bool function returns whether the zombie is killed after the bullet
	bool GetZombieAlive();	//bool function returns whether the zombie is alive or not
	bool GetBloodShown();	//bool function returns whether the blood is shown on screen
	bool CheckCollisions(Point2D a_oPosition);
};

#endif //__ZOMBIE_H__
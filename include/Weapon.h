////////////////////////////////////////////////////////////
// File: Weapon.h
// Author: Emmanuel Vaccaro
// Date: 17/03/2014
// Brief: Used for handling the weapon object properties
////////////////////////////////////////////////////////////
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "GameObject.h"
#include "MuzzleFlash.h"
#include "Bullet.h"
#include "Textures.h"
#include <math.h>

class Weapon : public GameObject, public Textures //Multiple inheritance - GameObject and Textures
{
private:
	int m_fBulletX, m_fBulletY;				//Used to obtain the bullet position
	int m_iCurrentBullet;					//Used to set the current bullet index for the bullet pointer array
	bool m_bCurrentMouse;					//Used to obtain the mouse down state
	int m_iClipAmount;						//Used to set the bullet amount allowed on screen
	int m_iRateOfFire;						//Used to set the weapon's rate of fire (NOTE: It's inverted. e.g. 10 is faster than 0.)
	MuzzleFlash* oMuzzleFlash;				//Used to create new muzzle flash objects
	Bullet** m_oBullet;						//Used to create new bullet objects
public:
	Weapon();	//Default constructor
	~Weapon();	//Default deconstructor
	Weapon(int a_iWidth, int a_iHeight, Point2D position); //Custom constructor
	void Update(float m_fDirection, Point2D o_PlayerPosition, int a_iScreenWidth, int a_iScreenHeight, Zombie** a_oZombie); //Update function for weapon
	void Draw();	//Draw function for weapon
	void Shoot(float a_fDirection);	//void function used for shooting new bullets
	void InitialiseBullet();		//void function used for initialising the bullet pointer array
	void CreateNewBullet();			//void function used to create a new bullet pointer
	void GetTexture();				//void function used to obtain the texture for weapon object
};

#endif //__WEAPON_H__
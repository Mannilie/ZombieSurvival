////////////////////////////////////////////////////////////
// File: Bullet.h
// Author: Emmanuel Vaccaro
// Date: 10/03/2014
// Brief: Handles the bullet game object.
////////////////////////////////////////////////////////////
#ifndef __BULLET_H__
#define __BULLET_H__

#include "ZombieBox.h"
#include "GameObject.h"
#include "Zombie.h"

class Bullet : public GameObject	//Inherits GameObject
{
private:
	float m_fDiffX, m_fDiffY;	//Stores the difference between one sprite location to another (trigonometry math)
	float m_fBulletSpeed;		//Stores the bullet's speed as a float
	int m_iZombieAmount;		//Stores the zombie amount declared in "GameObject"
	int m_iBulletDamage;		//Stores the bullet's damage
	bool m_bAlive;				//Used to check if the bullet exists
	float m_fdPI;				//Used to store PI from "GameObject"
	float m_fLength;			//Used to store the length calculated between the square root of the angle between the mouse and the player
public:
	Bullet();	//Default constructor
	~Bullet();	//Default deconstructor
	Bullet(bool a_bAlive, int a_iWidth, int a_iHeight, Point2D position);	//Custom constructor
	void Update(Point2D a_oPosition, int a_iScreenWidth, int a_iScreenHeight, Zombie** a_oZombie);	//Update function that takes in a zombie pointer array
	void FireBullet(float a_fDirection, Point2D a_oPlayerPosition, int x, int y);	//void function used to get the bullet's angle and direction
	Point2D GetBulletLocation();	//Obtains the location of the bullet when called and returns a Point2D
	void DestroyBullet();			//Destroys the sprite texture
	bool BulletAlive();				//Checks if bullet still exists
	void Draw();					//Draws the bullet
};

#endif	//__BULLET_H__
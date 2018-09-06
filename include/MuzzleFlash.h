////////////////////////////////////////////////////////////
// File: MuzzleFlash.h
// Author: Emmanuel Vaccaro
// Date: 14/03/2014
// Brief: Used to handle the game object "Muzzle Flash"
////////////////////////////////////////////////////////////
#ifndef __MUZZLEFLASH_H__
#define __MUZZLEFLASH_H__

#include "Textures.h"
#include "GameObject.h"

class MuzzleFlash : public GameObject, public Textures //Multiple inheritance - GameObject and Textures class
{
private:
	bool m_bAlive;	//Used to check if the muzzle flash is alive
public:
	MuzzleFlash();	//Default constructor
	~MuzzleFlash();	//Default deconstructor
	MuzzleFlash(int a_iWidth, int a_iHeight, Point2D position);	//Custom constructor
	void Update(Point2D a_oPosition, float a_fDirection);	//Update function
	void Draw();	//Draw function
	void GetTexture();	//GetTexture function used to obtain the texture measurements from "Textures" class
};

#endif //__MUZZLEFLASH_H__
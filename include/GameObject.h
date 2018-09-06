////////////////////////////////////////////////////////////
// File: GameObject.h
// Author: Emmanuel Vaccaro
// Date: 17/03/2014
// Brief: Used as a blueprint for all game object creations.
////////////////////////////////////////////////////////////
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Point2D.h"

class GameObject
{
protected:
	unsigned int* m_uiClippedTextures;	//Used to store Textures of objects that are clipped from png files
	unsigned int m_uiTexture;		//Used to store the texture for all game objects
	unsigned int m_uiZombieBlood;	//Used to store the zombie blood for the zombie game object once only
	Point2D m_oPosition;		//Used to store (X and Y) position of objects
	Point2D m_oVelocity;		//Used to store (X and Y) velocity of objects
	Point2D m_oCollisionVelocity; //Used to store the velocity for collision detection
	float m_fDirection;			//Used to get direction in Degrees rather than Radians
	int m_iWidth, m_iHeight;	//Sets width and height of object to an int
	
	float m_fCamX, m_fCamY;		//Used to obtain the "Get Camera Position" only by using a float
	int m_iCamX, m_iCamY;		//Used for converting the float versions (m_fCamX & m_fCamY) to ints
	int m_iMouseX, m_iMouseY;	//Used for obtaining the mouse position
	Point2D m_iMousePosition;	//Sets the mouse position variables
public:
	GameObject();				//Default constructor
	~GameObject();				//Default deconstructor
	Point2D GetMousePosition();	//Obtains the mouse position for all objects
	virtual const float GetPI();			//Virtual class to return constant PI
	virtual const int GetMapDimensions();	//Virtual class to return the constant Map Dimensions
	virtual const int GetScreenWidth();		//Virtual class to return the constant Screen Width
	virtual const int GetScreenHeight();	//Virtual class to return the constant Screen Height
	virtual const int GetZombieAmount();	//Virtual class to return the constant Zombie amount
};

#endif // __GAMEOBJECT_H__
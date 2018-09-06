////////////////////////////////////////////////////////////
// File: Player.h
// Author: Emmanuel Vaccaro
// Date: 10/03/2014
// Brief: Manages all textures that need to be modified with objects
////////////////////////////////////////////////////////////
#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include "Point2D.h"

class Textures
{
protected:
	unsigned int m_uiBloodTexture[4];	//Used to store all blood textures for the zombie class object only
	float* m_fSetViewportSize;	//Used to store VIEWPORT size of object's texture
	float* m_fSpriteOriginPtr;	//Used to store DRAW ORIGIN of the object
	float* m_fTileCoordsPtr;	//Used to crop the texture using specified COORDINATES of that texture
public:
	Textures();		//Default constuctor
	~Textures();	//Default deconstructor
	void SetViewportSize(float a_iWidth, float a_iHeight);	//void function to set the texture's viewport size
	void SetSpriteOrigin(float U, float V);	//void function to set the sprite's origin
	void SetCoordinates(float minU, float minV, float maxU, float maxV, const float fSheetWidth, const float fSheetHeight);	//void function to set the sprite's coordinates
	float* GetViewportSize();	//float* function that returns the viewport size
	float* GetSpriteOrigin();	//float* function that returns the spirte origin
	float* GetCoordinates();	//float* function that returns the sprite coordinates
	unsigned int GetZombieBlood(int a_iRandomBlood);	//Unsigned int function that returns the random zombie blood texture
};

#endif	// __TEXTURES_H__
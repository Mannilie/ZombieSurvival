#include "Textures.h"

Textures::Textures()
{
	m_fSetViewportSize	= new float[2];	//Initialises the viewport size as a new float array with 2 spaces
	m_fSpriteOriginPtr	= new float[2];	//Initialises the sprite origin as a new float array with 2 spaces
	m_fTileCoordsPtr	= new float[4];	//Initialises the coordinates size as a new float array with 2 spaces
	m_uiBloodTexture[0] = CreateSprite("./images/Zombies/frame0.png", 66, 73, true);	//Blood texture 1 is created
	m_uiBloodTexture[1] = CreateSprite("./images/Zombies/frame1.png", 50, 78, true);	//Blood texture 2 is created
	m_uiBloodTexture[2] = CreateSprite("./images/Zombies/frame2.png", 43, 84, true);	//Blood texture 3 is created
	m_uiBloodTexture[3] = CreateSprite("./images/Zombies/frame3.png", 42, 68, true);	//Blood texture 4 is created
}

Textures::~Textures()
{
	delete[] m_fSetViewportSize;	
	delete[] m_fSpriteOriginPtr;	//Deletes the pointers in the deconstructor
	delete[] m_fTileCoordsPtr;
}

void Textures::SetViewportSize(float a_iWidth, float a_iHeight)
{	
	m_fSetViewportSize[0] = a_iWidth;	//Sets the first array index value to the width
	m_fSetViewportSize[1] = a_iHeight;	//Sets the second array index value to the height
}

void Textures::SetSpriteOrigin(float U, float V)
{
	m_fSpriteOriginPtr[0] = U;	//Sets the first sprite origin array index value to U
	m_fSpriteOriginPtr[1] = V;	//Sets the second sprite origin array index value to V
}

void Textures::SetCoordinates(float m_fminX, float m_fminY, float m_fmaxX, float m_fmaxY, const float m_fTextureWidth, const float m_fTextureHeight)
{
	m_fTileCoordsPtr[0] = (m_fminX* (m_fSetViewportSize[0]) / m_fTextureWidth);		//Sets the first coordinates array index value to the cropped value
	m_fTileCoordsPtr[1] = (m_fminY* (m_fSetViewportSize[1]) / m_fTextureHeight);	//Sets the second coordinates array index value to the cropped value
	m_fTileCoordsPtr[2] = (m_fmaxX* (m_fSetViewportSize[0]) / m_fTextureWidth);		//Sets the third coordinates array index value to the cropped value
	m_fTileCoordsPtr[3] = (m_fmaxY* (m_fSetViewportSize[1]) / m_fTextureHeight);	//Sets the fourth coordinates array index value to the cropped value
}

float* Textures::GetViewportSize()
{
	return m_fSetViewportSize;	//Returns the sprite viewport size array
}

float* Textures::GetSpriteOrigin()
{
	return m_fSpriteOriginPtr;	//Returns the sprite origin array
}

float* Textures::GetCoordinates()
{
	return m_fTileCoordsPtr;	//Returns the sprite coordinates array
}

unsigned int Textures::GetZombieBlood(int a_iRandomBlood)
{
	return m_uiBloodTexture[a_iRandomBlood];
}
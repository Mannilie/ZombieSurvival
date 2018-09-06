#include "MuzzleFlash.h"

MuzzleFlash::MuzzleFlash(){}
MuzzleFlash::~MuzzleFlash(){}

MuzzleFlash::MuzzleFlash(int a_iWidth, int a_iHeight, Point2D position)
{
	m_iWidth	= a_iWidth;	//Sets the muzzle flash's width
	m_iHeight	= a_iHeight;//Sets the muzzle flash's height
	m_oPosition = position;	//Sets the position of muzzle flash to the player's
	GetTexture();	//Calls the "GetTexture" function to get the texture from "Textures" class
	m_uiTexture = CreateSprite("./images/Player/MuzzleFlash.png", m_fSetViewportSize, m_fSpriteOriginPtr, m_fTileCoordsPtr);	//Creates the muzzle flash sprite
}

void MuzzleFlash::Update(Point2D a_oPosition, float a_fDirection)
{
	RotateSprite(m_uiTexture, a_fDirection);	//Rotates the sprite relative to the players direction
	MoveSprite(m_uiTexture, a_oPosition.x, a_oPosition.y); //Moves the sprite
}

void MuzzleFlash::Draw()
{
	DrawSprite(m_uiTexture); //Draws the muzzle flash sprite
}

void MuzzleFlash::GetTexture()
{
	SetViewportSize((float)m_iWidth, (float)m_iHeight);				//Sets Sprite's VIEWPORT size (Width and Height)
	SetSpriteOrigin(13, -45);										//Sets Sprite's DRAWN origin (where it's drawn from)
	SetCoordinates(0, 0, 1, 1, (float)m_iWidth, (float)m_iHeight);	//Sets Sprite's SKETCH Coordinates (Minimum U, Minimum V, Maximum U, Maximum V, Width, Height)
}
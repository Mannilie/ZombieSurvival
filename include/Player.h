////////////////////////////////////////////////////////////
// File: Player.h
// Author: Emmanuel Vaccaro
// Date: 14/03/2014
// Brief: Used to manage the player object
////////////////////////////////////////////////////////////
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Gameobject.h"
#include "PlayerBox.h"

class Player : public GameObject //Inherits GameObject
{
private:
	int m_iPlayerGreen, m_iPlayerBlue;	//Used to store the green and blue colours for SColour
	float m_fHealthDrainTimer;			//Used as a timer for player's health drainage
	float m_fDiffX, m_fDiffY;			//Stores the difference between one sprite location to another (trigonometry math)
	char m_cHealth[64];					//Used to store the player's health after it's converted with itoa
	float PlayerAngle;					//Used to obtain the player's angle between the mouse and the player position
	int m_iWalkTimer;					//Used as a timer for the player to walk using the player's given velocity (m_oVelocity)
	float m_fLength;					//Used to obtain the triangular length for the player's angle calculation
	int m_iHealth;						//Used to store the player's health
	PlayerBox* m_oPlayerBox;
public:
	Player();	//Default constructor
	~Player();	//Default deconstructor
	Player(unsigned int a_uiTexture, int a_iWidth, int a_iHeight, Point2D a_oPosition);	//Custom constructor
	void Update(float a_fDirection);	//Update function (updates player sprite)
	void Draw();	//Draw function (draws player sprite)
	float GetDirection(float a_dPI);	//float function that calculates the direction (angle) given the mouse location and player location
	Point2D GetPlayerPos();	//Point2D function returns the current player position
	int GetPlayerHealth();	//int function that returns the player's current health
	void PlayerHit();	//void function that is called from "Zombie" and decreases the player's health
	bool CheckCollisions(Point2D a_oPosition);
};

#endif //__PLAYER_H__
#include "Player.h"
#include <math.h>
#include <stdlib.h>

Player::Player(){}
Player::~Player()
{
	delete m_oPlayerBox;
}	

Player::Player(unsigned int a_uiTexture, int a_iWidth, int a_iHeight, Point2D a_oPosition)
{
	m_uiTexture		= a_uiTexture;	//Obtains the passed player texture
	m_iWidth		= a_iWidth;		//Sets the player's width
	m_iHeight		= a_iHeight;	//Sets the player's height
	m_oPosition		= a_oPosition;	//Sets the player's position
	m_oVelocity.x	= 1;			//Sets the player's velocity on the X & Y axis (Player Speed)
	m_oVelocity.y	= 1;
	m_iPlayerGreen	= 255;			//Sets the player's Green and Blue colors to default
	m_iPlayerBlue	= 255;
	m_iHealth		= 100;			//Sets the player's health to 100
	m_iWalkTimer	= 0;			//Initialises the walk timer
	m_fHealthDrainTimer	= 0;		//Initialises the health drainage timer
	m_oPlayerBox		= new PlayerBox(m_iWidth, m_iHeight, m_oPosition);	//Creates the player collision
	SetSpriteColour(m_uiTexture, SColour(255, m_iPlayerGreen, m_iPlayerBlue, 255));	//Sets player sprite back to original colour
}

void Player::Update(float a_fDirection)
{
	m_iWalkTimer++;	//Increments walk timer
	if(m_iWalkTimer >= 20)	//Checks if walk timer has hit 20 frames
	{
		m_iWalkTimer = 0;	//Sets the timer back to 0
		if(IsKeyDown(KEY_RIGHT) || IsKeyDown('D'))	//Checks if the "D" key or the "RIGHT" key has been pressed
		{
			m_oPosition.x += m_oVelocity.x; //Moves player right
			if(m_oPosition.x + 21 >= 1800) //Checks if the player is off the right of the screen
			{
				m_oPosition.x -= m_oVelocity.x;	//Puts the X position back one position
			}
		}
		if(IsKeyDown(KEY_LEFT) || IsKeyDown('A'))	//Checks if the "A" key or the "LEFT" key has been pressed
		{
			m_oPosition.x -= m_oVelocity.x; //Moves player left
			if(m_oPosition.x - 21 <= 0)	//Checks if the player is off the left of the screen
			{
				m_oPosition.x += m_oVelocity.x; //Puts the X position back one position
			}
		}
		if(IsKeyDown(KEY_UP) || IsKeyDown('W'))	//Checks if the "W" key or the "UP" key has been pressed
		{
			m_oPosition.y -= m_oVelocity.y; //Moves player up
			if(m_oPosition.y - 21 <= 0) //Checks if the player is off the top of the screen
			{
				m_oPosition.y += m_oVelocity.y;	//Puts the Y position back one position
			}
		}
		if(IsKeyDown(KEY_DOWN) || IsKeyDown('S'))	//Checks if the "S" key or the "DOWN" key has been pressed
		{
			m_oPosition.y += m_oVelocity.y; //Moves player down
			if(m_oPosition.y + 21 >= 1800) //Checks if the player is off the bottom of the screen
			{
				m_oPosition.y -= m_oVelocity.y;	//Puts the Y position back one position
			}
		}	
	}	
	m_oPlayerBox->Update(m_oPosition);
	RotateSprite(m_uiTexture, a_fDirection);	//Rotates player towards the mouse location
	MoveSprite(m_uiTexture, m_oPosition.x, m_oPosition.y);	//Moves sprite to new position

	GetCameraPosition(m_fCamX, m_fCamY);	//Get's the camera position
	m_iCamX = (int)m_fCamX;	//Converts floats to int of the camera
	m_iCamY = (int)m_fCamY;
	_itoa_s(m_iHealth, m_cHealth, 10);	//Converts the integer to a char
	DrawString("Health:", m_iCamX + 20, m_iCamY + 2);	//Draws "Health" text
	DrawString(m_cHealth, m_iCamX + 110, m_iCamY + 2);	//Draws the health amount
}

void Player::Draw()
{
	DrawSprite(m_uiTexture);	//Draws the player sprite
}

Point2D Player::GetPlayerPos()
{
	return m_oPosition;	//Returns player position
}

float Player::GetDirection(float a_dPI)
{
	m_iMouseX = GetMousePosition().XAxis;	//Gets mouse location
	m_iMouseY = GetMousePosition().YAxis;
	m_fDiffX = m_iMouseX - m_oPosition.x;	//Gets the difference between mouse and player positions
	m_fDiffY = m_iMouseY - m_oPosition.y;
	m_fLength = sqrt(m_fDiffX*m_fDiffX + m_fDiffY*m_fDiffY);	//Calculates the length of the triangle
	if(m_fLength != 0)	//Checks if the length is not at 0
	{
		m_fDiffX = m_fDiffX/m_fLength;	//Normalise differences
		m_fDiffY = m_fDiffY/m_fLength;
	}
	m_fDirection = (atan2(m_fDiffX, m_fDiffY)* 180/a_dPI); //Get the new direction for the player
	return m_fDirection;	//Return the direction
}

void Player::PlayerHit()
{
	if(m_fHealthDrainTimer >= 300)	//Checks how long the zombie is hitting the player
	{
		m_iHealth		-= 25;		//Player takes damage from zombie
		m_iPlayerGreen	-= 64;		//Decreases the green color of the player sprite
		m_iPlayerBlue	-= 64;		//Decreases the blue color of the player sprite
		m_fHealthDrainTimer	= 0;		//Timer resets
	}
	SetSpriteColour(m_uiTexture, SColour(255, m_iPlayerGreen, m_iPlayerBlue, 255)); //Sets the player sprite's colour
	m_fHealthDrainTimer++;	//Increments the health drainage timer
}

int Player::GetPlayerHealth()
{
	return m_iHealth;	//Returns player's health
}

bool Player::CheckCollisions(Point2D a_oPosition)
{
	return m_oPlayerBox->CheckForCollisions(a_oPosition);
}
#include "Bullet.h"
#include <math.h>
#include <stdlib.h>

Bullet::Bullet(){}
Bullet::~Bullet(){}

Bullet::Bullet(bool a_bAlive, int a_iWidth, int a_iHeight, Point2D position)
{
	m_bAlive	= a_bAlive;		//Sets the bullet to a value passed into the class
	m_iHeight	= a_iHeight;	//Sets the bullet's height
	m_iWidth	= a_iWidth;		//Sets the bullet's width
	m_oPosition = position;		//Sets the bullet's starting position
	m_iBulletDamage = 20;		//Sets the bullet's (default) damage when hitting a zombie NOTE: This is randomised between 20 and 40 later
	m_fBulletSpeed = 0.9f;		//Sets the bullet's speed
	m_iZombieAmount = GetZombieAmount();	//Obtains the zombie's amount from "GameObject" (inherited)
	m_fdPI = GetPI();			//Gets PI from "GameObject"
	m_uiTexture = CreateSprite("./images/Player/Bullet.png", 5, 25, true);	//Creates the sprite inside the custom constructor
}

void Bullet::Update(Point2D a_oPosition, int a_iScreenWidth, int a_iScreenHeight, Zombie** a_oZombie)
{
	if(m_bAlive == true)	//Checks if the bullet exists
	{
		m_oPosition.x += m_oVelocity.x;	
		m_oPosition.y += m_oVelocity.y;
		MoveSprite(m_uiTexture, m_oPosition.x, m_oPosition.y); //Moves the bullet according to the calculated velocity from the "FireBullet" function

		m_iBulletDamage = rand() % 40 + 20;	//Randomises the damage of the bullet from 20 to 40

		if(m_oPosition.x >= 1800 || m_oPosition.x <= 0 || m_oPosition.y >=  1800 || m_oPosition.y <= 0)	//Checks if the bullet goes off the map
		{
			m_bAlive = false;	//Bullet no longer exists if it's out of the map dimensions
		}
		
		for(int i = 0; i < m_iZombieAmount; i++)	//Goes through and checks each zombie to see if the bullet has entered it's collision
		{
			if(a_oZombie[i] != nullptr && a_oZombie[i]->GetBloodShown() == false) //Checks if the bullet hit the zombie's collision and if the blood splatter is shown
			{
				if(a_oZombie[i]->CheckCollisions(m_oPosition))
				{
					m_bAlive = false;	//Bullet no longer exists if it's hit a zombie
					a_oZombie[i]->ZombieHit(m_iBulletDamage);	//Calls the "ZombieHit" function to take health away from the zombie that the bullet has hit
					break;	//Ends the for loop
				}
			}
		}
	}
}

void Bullet::Draw()
{
	DrawSprite(m_uiTexture);	//Draws the bullet texture sprite
}

void Bullet::FireBullet(float a_fDirection, Point2D a_oPlayerPosition, int x, int y)
{	
	m_bAlive = true;	//The bullet exists once the weapon has called this function
	m_oPosition = a_oPlayerPosition;	//Sets the bullet's position to the player's position
	m_iMouseX = GetMousePosition().XAxis;	//Gets the mouse position
	m_iMouseY = GetMousePosition().YAxis;	
	m_fDiffX = m_iMouseX - m_oPosition.x;	//Obtains the difference between the X & Y location of the Bullet and the mouse location
	m_fDiffY = m_iMouseY - m_oPosition.y;	

	m_fLength = sqrt(m_fDiffX*m_fDiffX + m_fDiffY*m_fDiffY); //Obtains the actual length from the Bullet to the mouse

	if(m_fLength != 0) //Checks if the vector is not equal to 0
	{
		m_fDiffX = m_fDiffX/m_fLength;	//Calculates the NORMALISED difference between the Bullet and the mouse location
		m_fDiffY = m_fDiffY/m_fLength;
	}
	
	m_fDirection = (atan2f(m_fDiffX, m_fDiffY)* 180/m_fdPI); //Obtains the angle for rotation ONLY


	m_oVelocity.x += m_fDiffX * m_fBulletSpeed; //Moves the bullet along the set angle of DiffX and DiffY
	m_oVelocity.y += m_fDiffY * m_fBulletSpeed;

	
	RotateSprite(m_uiTexture, a_fDirection); //Rotates the bullet to the angle facing the mouse location
}

bool Bullet::BulletAlive()
{
	return m_bAlive;	//Returns the bullet's existance
}

void Bullet::DestroyBullet()
{
	DestroySprite(m_uiTexture);	//Draws the bullet
}

Point2D Bullet::GetBulletLocation()
{
	return m_oPosition;	//Returns the bullet's location
}
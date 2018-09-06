#include "Zombie.h"

Zombie::Zombie(){}
Zombie::~Zombie()
{
	delete m_oZombieBox;
}

Zombie::Zombie(bool a_bAlive, int a_iWidth, int a_iHeight, Point2D a_oPosition, float a_oZombieSpeed, int a_iRandomBlood)
{
	m_bAlive			= a_bAlive;			//Sets the zombie to alive
	m_iHeight			= a_iHeight;		//Sets the zombie sprite's height
	m_iWidth			= a_iWidth;			//Sets the zombie sprite's width
	m_oPosition			= a_oPosition;		//Sets the zombie's position
	m_iZombieHealth		= 100;				//Sets the zombie's health to 100
	m_iShowHealthTimer	= 0;				//Initialises the show health timer
	m_iZombieAliveTimer = 0;				//Initialises the zombie's alive timer (after the blood splatter is thrown)
	m_bShowHealth		= false;			//Doesn't show the health
	m_bZombieKilled		= false;			//Zombie is set to alive
	m_bBloodShown		= false;			//Blood isn't shown
	m_fZombieSpeed		= a_oZombieSpeed;	//Zombie speed is given a random number from "ZombieSpawner" class
	m_oZombieBox		= new ZombieBox(m_iWidth, m_iHeight, m_oPosition);	//Creates the zombie collision
	m_uiTexture			= CreateSprite("./images/Zombies/Zombie.png", m_iWidth, m_iHeight, true);	//Zombie texture is created
	m_uiZombieBlood		= GetZombieBlood(a_iRandomBlood);	//Zombie blood texture is created
	a_dPI = GetPI();	//PI is obtained from "GameObject" class
}

void Zombie::Update(float a_oPlayerPositionX, float a_oPlayerPositionY, Player* a_oPlayer)
{
	if(m_iZombieHealth > 0)	//Checks if the zombie still has health
	{
		DeployZombie(a_oPlayerPositionX, a_oPlayerPositionY);	//Deploys the zombie
		if(a_oPlayer->CheckCollisions(m_oPosition))	//Checks if the zombie is within the player's collision
		{
			a_oPlayer->PlayerHit();	//If true hit player
		}
		else
		{
			m_oPosition.x += m_oVelocity.x;	//Move zombie's position close to player's
			m_oPosition.y += m_oVelocity.y;
		}
		if(m_bShowHealth) //Checks if the health is showing
		{

			m_oPosition.XAxis = (int)m_oPosition.x;	//Get the zombie's position converted from a float to an int
			m_oPosition.YAxis = (int)m_oPosition.y;
			_itoa_s(m_iZombieHealth, m_cHealth, 10);
			DrawString(m_cHealth, m_oPosition.XAxis - 20, m_oPosition.YAxis - 40);
			if(m_iShowHealthTimer >= 1000)	//Check if the health timer is above a certain frame
			{
				m_bShowHealth = false;	//Don;t show the health on screen
				m_iShowHealthTimer = 0;	//Reset timer
			}
			m_iShowHealthTimer++;	//Increment the health timer
		}
		MoveSprite(m_uiTexture, m_oPosition.x, m_oPosition.y);	//Move the zombie sprite closer to the player sprite
	}else{	//Executes these lines if the zombies health is less than or equal to 0
		m_bBloodShown = true;		//Show the blood
		m_bZombieKilled = true;		//Zombie is killed
		if(m_iZombieAliveTimer >= 1000)	//Shows the blood for a certain amount of time
		{
			m_bAlive = false;	//Finally sets zombie to non-existent so the pointer can be destroyed elsewhere
		}
		if(m_iZombieAliveTimer >= 1)	//Increments the zombie kills for the player
		{
			m_bZombieKilled = false;	//Zombie has been killed but this is set to false so the zombie kills can only be incremented by 1 elsewhere
		}
		m_iZombieAliveTimer++; //Increments alive timer
		RotateSprite(m_uiZombieBlood, m_fZombieAngle);	//Rotates the zombie blood to the angle where the player last hit the zombie
		MoveSprite(m_uiZombieBlood, m_oPosition.x, m_oPosition.y);	//Moves the blood to the position where the zombie was killed
	}
	m_oZombieBox->Update(m_oPosition);
}

void Zombie::Draw()
{
	if(m_bBloodShown == false) //Checks if blood isn't showing
	{
		DrawSprite(m_uiTexture);	//Draws the zombie
	}
	else
	{
		DrawSprite(m_uiZombieBlood); //Draws the blood
	}
}

void Zombie::DeployZombie(float a_oPlayerPositionX, float a_oPlayerPositionY)
{
	m_fZombieAngle = atan2f(a_oPlayerPositionX - m_oPosition.x, a_oPlayerPositionY - m_oPosition.y);	//Gets the angle for the zombie given the player location and the current zombie position
	m_fZombieAngle = m_fZombieAngle * (180/a_dPI);		//Converts radians to degrees
	m_oVelocity.x = sin((m_fZombieAngle) * a_dPI/180) / m_fZombieSpeed;	//Calculates the direction for the zombie to walk towards
	m_oVelocity.y = cos((m_fZombieAngle) * a_dPI/180) / m_fZombieSpeed;
	RotateSprite(m_uiTexture, m_fZombieAngle);	//Rotates the zombie toward the player
}

bool Zombie::GetZombieAlive()
{
	return m_bAlive;	//Returns the zombie's existence status
}

void Zombie::ZombieHit(int a_iBulletDamage)
{
	m_iZombieHealth -= a_iBulletDamage;	//Decreases zombies health when bullet hits it
	m_bShowHealth = true;				//Shows the zombie's health
}

Point2D Zombie::GetZombiePos()
{
	return m_oPosition;	//Returns zombie's current position
}

bool Zombie::GetZombieKilled()
{
	return m_bZombieKilled;	//Returns true if the zombie's health is below 0
}

bool Zombie::GetBloodShown()
{
	return m_bBloodShown;	//Returns true if the blood shown on screen
}

bool Zombie::CheckCollisions(Point2D a_oPosition)
{
	return m_oZombieBox->CheckForCollisions(a_oPosition);
}
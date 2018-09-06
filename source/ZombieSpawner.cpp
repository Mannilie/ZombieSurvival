#include "ZombieSpawner.h"
ZombieSpawner::ZombieSpawner()
{
	m_iZombiesKilled = 0;					//Sets the zombie kills to 0
	m_iZombieAmount = GetZombieAmount();	//Gets the zombie amount
	m_iMapDimension = GetMapDimensions();	//Gets the map's dimensions
	InitialiseZombies();					//Initialises all zombies
}

ZombieSpawner::~ZombieSpawner()
{
	delete[] m_oZombie;	//Deletes zombie pointer
}

void ZombieSpawner::UpdateZombies(Player* m_oPlayer)
{
	for(int i = 0; i < m_iZombieAmount; i++)
	{
		m_fRandX = (float)(rand() % 1800);	//Obtains a random value for X
		m_fRandY = (float)(rand() % 1800);	//Obtains a random value for Y
		m_iRandomZombieSpawn = rand() % 4 + 1;	//Obtains a random value for the switch statement between 1 and 4
		switch(m_iRandomZombieSpawn)	//Gives zombie a random spawn location
		{
			case 1: //Sets the random spawn location along the top of the screen
				oRandZombieSpawn.x = m_fRandX;	
				oRandZombieSpawn.y = 0 - 40;
				break;
			case 2: //Sets the random spawn location along the left of the screen
				oRandZombieSpawn.x = 0 - 40;
				oRandZombieSpawn.y = m_fRandY;
				break;
			case 3: //Sets the random spawn location along the right of the screen
				oRandZombieSpawn.x = m_fRandX;
				oRandZombieSpawn.y = (float)m_iMapDimension + 40;
				break;
			case 4: //Sets the random spawn location along the bottom of the screen
				oRandZombieSpawn.x = (float)m_iMapDimension + 40;
				oRandZombieSpawn.y = m_fRandY;
		}
		if(m_oZombie[i] == nullptr) //Checks if the current zombie is a nullptr
		{
			m_fZombieSpeed = (float)(rand() % 30 + 22); //Obtains a random number between 24 and 30 to act as the zombie's speed
			m_iRandomBlood = rand() % 4;	//Obtains a random number between 0 and 4
			m_oZombie[i] = new Zombie(true, 40, 40, oRandZombieSpawn, m_fZombieSpeed, m_iRandomBlood); //Spawns zombies in random locations on the outer sides of the screen
		}
	}
	for(int i = 0; i < m_iZombieAmount; i++)
	{
		if(m_oZombie[i] != nullptr)	//Checks if the zombie is not a nullptr
		{
			if(m_oZombie[i] -> GetZombieAlive() == false)	//Checks if the zombie isn't alive
			{
				delete m_oZombie[i];	//Deletes zombie
				m_oZombie[i] = nullptr;	//Re-initialises zombie
			}
		}
		if(m_oZombie[i] != nullptr) //Checks if the zombie is not a nullptr
		{
			if(m_oZombie[i] -> GetZombieKilled() == true)	//Checks if the zombie is killed
			{
				m_iZombiesKilled++;	//Increments the zombie kills to be desplayed to the player
			}
		}
		if(m_oZombie[i] != nullptr) //Checks if the zombie is not a nullptr
		{
			m_oZombie[i] -> Update(m_oPlayer->GetPlayerPos().x, m_oPlayer->GetPlayerPos().y, m_oPlayer);	//Updates the zombie if it's alive
		}
	}
}

Zombie** ZombieSpawner::ReturnZombie()
{
	return m_oZombie;	//Returns the zombie pointer array
}

void ZombieSpawner::DrawZombies()
{
	for(int i= 0; i < m_iZombieAmount; i++)
	{
		if(m_oZombie[i] != nullptr)	//Checks if the zombie array index isn't empty
		{
			m_oZombie[i]->Draw();	//Draws the zombie
		}
	}
}

int ZombieSpawner::CurrentZombiesKilled()
{
	return m_iZombiesKilled;	//Returns the zombies killed integer to be desplayed to the player
}

void ZombieSpawner::InitialiseZombies()
{
	m_oZombie = new Zombie*[m_iZombieAmount];	//Creates a new pointer array for zombie
	for(int i = 0; i < m_iZombieAmount; i++)
	{
		m_oZombie[i] = nullptr;	//Initialises the zombie
	}
}
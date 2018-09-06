#include "Weapon.h"

Weapon::Weapon(){}

Weapon::~Weapon()
{
	delete[] m_oBullet;		//Deletes the bullet pointer array
	delete oMuzzleFlash;	//Deletes the muzzle flash pointer
}

Weapon::Weapon(int a_iWidth, int a_iHeight, Point2D a_oPosition)
{
	m_iHeight		= a_iHeight;		//Sets the weapon's height
	m_iWidth		= a_iWidth;			//Sets the weapon's width
	m_oPosition		= a_oPosition;		//Sets the weapon's position
	m_iRateOfFire	= 5;				//Sets the rate of fire
	m_iClipAmount	= 10;				//Sets the amount of bullets
	oMuzzleFlash	= new MuzzleFlash;	//Creates new memory for the muzzle flash object
	oMuzzleFlash	= nullptr;			//Initialises the muzzle flash object
	InitialiseBullet();					//Initialises the bullets by calling the "InitialiseBullet" function
	GetTexture();						//Gets the modified texture for the weapon sprite
	m_uiTexture = CreateSprite("./images/Weapons/LMG.png", m_fSetViewportSize, m_fSpriteOriginPtr, m_fTileCoordsPtr);	//Creates the weapon sprite in "m_uiTexture)
}

void Weapon::Update(float a_fDirection, Point2D a_oPlayerPosition, int a_iScreenWidth, int a_iScreenHeight, Zombie** a_oZombie)
{
	m_fDirection = a_fDirection;		//Sets weapon direction to the player's direction
	m_oPosition = a_oPlayerPosition;	//Sets the weapon position to the player's position
	m_bCurrentMouse = GetMouseButtonDown(MOUSE_BUTTON_1);	//Sets "m_bCurrentMouse" to true if the mouse is clicked
	if(m_bCurrentMouse == true)	//Checks if the mouse is cicked
	{
		if(m_iRateOfFire >= 50) //Checks if the rate of fire is above a certain amount of frames frames
		{
			delete oMuzzleFlash;	//Deletes the muzzle flash object from the screen
			oMuzzleFlash = nullptr;	//Re-initialises the pointer
		}
		if(m_iRateOfFire == 1300)	//Checks if the rate of fire is above a certain amount of frames
		{
			CreateNewBullet();		//Calls the "CreateNewBullet" function to create the bullet
			Shoot(a_fDirection);	//Calls the "Shoot" function to shoot the bullet
			m_iRateOfFire = 0;		//Sets the rate of fire back to 0
		}	
		m_iRateOfFire++; //Increments rate of fire
	}else{
		delete oMuzzleFlash;	//Deletes the muzzle flash object from the screeen if nothing is clicked
		oMuzzleFlash = nullptr;	//Re-initialises the pointer
	}
	if(oMuzzleFlash != nullptr)	//Checks if muzzle flash is a nullptr
	{
		oMuzzleFlash -> Update(m_oPosition,  m_fDirection); //Updates the muzzle flash object if it isn't a nullptr
	}
	for(int i = 0; i < m_iClipAmount; i++)	//Updates bullets if there are bullets exist on screen
	{
		if(m_oBullet[i] != nullptr)
		{
			m_oBullet[i] -> Update(m_oPosition, 900, 900, a_oZombie);	//Updates bullet
			if(m_oBullet[i]->BulletAlive() == false)	//Checks if the bullet is dead
			{
				delete m_oBullet[i];	//Deletes the bullet that isn't alive
				m_oBullet[i] = nullptr;	//Re-initialises the bullet
			}
		}
	}
	RotateSprite(m_uiTexture, m_fDirection);	//Rotates the weapon to the player's direction
	MoveSprite(m_uiTexture, m_oPosition.x, m_oPosition.y);	//Moves the weapon with the player
}

void Weapon::Draw()
{
	DrawSprite(m_uiTexture);	//Draws weapon
	if(oMuzzleFlash != nullptr)	//Checks if the muzzle flash exists
	{
		oMuzzleFlash -> Draw();	//Draw muzzle flash if it does exist
	}
	for(int i = 0; i < m_iClipAmount; i++)
	{
		if(m_oBullet[i] != nullptr)	//Checks if bullet exists
		{
			m_oBullet[i]->Draw();	//Draws bullet if it does exist
		}
	}
}

void Weapon::GetTexture()
{
	SetViewportSize((float)m_iWidth, (float)m_iHeight);							//Sets Sprite's VIEWPORT size (Width and Height)
	SetSpriteOrigin(13, 0);														//Sets Sprite's DRAWN origin (where it's drawn from)
	SetCoordinates(0, 0, 1, 1, (const float)m_iWidth, (const float)m_iHeight);	//Sets Sprite's SKETCH Coordinates (Minimum U, Minimum V, Maximum U, Maximum V, Width, Height)
}

void Weapon::Shoot(float a_fDirection)
{
	m_fBulletX = GetMousePosition().XAxis;	//Obtains the mouse position and passes it to the bullet for calculation
	m_fBulletY = GetMousePosition().YAxis;
	m_oBullet[m_iCurrentBullet] -> FireBullet(a_fDirection, m_oPosition, m_fBulletX, m_fBulletY);	//Fires a bullet
}

void Weapon::CreateNewBullet()
{
	if(oMuzzleFlash == nullptr)	//Checks if the muzzleflash is a nullptr
	{
		oMuzzleFlash = new MuzzleFlash(13, 11, m_oPosition);	//Create a new muzzle flash object if it is a nullptr
	}
	for(int i = 0; i < m_iClipAmount; i++)
	{
		if(m_oBullet[i] == nullptr)	//Check if the bullet is a nullptr
		{
			m_oBullet[i] = new Bullet(true, 5, 25, m_oPosition);	//Create a new bullet if it is a nullptr
			m_iCurrentBullet = i;	//Set the current bullet to be shot to the bullet's index
			break;	//Exits the loop
		}
	}
}

void Weapon::InitialiseBullet()
{
	m_oBullet = new Bullet*[m_iClipAmount];	//Creates new bullets into an array
	for(int i = 0; i < m_iClipAmount; i++)	
	{
		m_oBullet[i] = nullptr;	//Initialises each bullet as a nullptr
	}	
}





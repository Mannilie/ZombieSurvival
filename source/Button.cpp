#include "Button.h"

Button::Button(){}
Button::~Button(){}
	
Button::Button(const char* a_cButtonTexture, int a_iWidth, int a_iHeight, Point2D a_oPosition)
{
	m_bButtonClicked = false;
	m_bHovered = false;					//Sets all button states to false
	m_bPushed = false;
	ButtonTexture	= a_cButtonTexture;	//Sets the button texture to the texture passed into the class
	m_iWidth			= a_iWidth;		//Sets Button width to the width that's passed into the class
	m_iHeight			= a_iHeight;	//Sets Button Height to the height that's passed into the class
	m_oPosition			= a_oPosition;	//Position is half of the screen width
	GetTexture();	//Calls the "GetTexture function
	m_uiTexture = m_iButtonState[0];	//Sets the current texture to the "idle" button of each texture
}

void Button::GetTexture()
{
	SetViewportSize((float)m_iWidth, (float)m_iHeight / 3);	//Sets Sprite's VIEWPORT size (Width and Height)
	SetSpriteOrigin(0.5, 0.5);								//Sets Sprite's DRAWN origin (where it's drawn from)

	for(int i = 0; i < 3; i++)	
	{
		SetCoordinates(0, (float)i, 1, (float)i + 1, (float)m_iWidth, (float)m_iHeight); //Clips the texture into separate peices 
		m_iButtonState[i] = CreateSprite(ButtonTexture, GetViewportSize(),GetSpriteOrigin(), GetCoordinates()); //Inserts clipped textures into an unsigned int array
	}	
}

void Button::Update(const int a_iScreenWidth, const int a_iScreenHeight)
{
	GetCameraPosition(m_fCamX, m_fCamY);	//Gets camera position
	m_oPosition.x = m_fCamX + ((float)a_iScreenWidth);	//Sets the button position to the centre of the camera.
	m_oPosition.y = m_fCamY + ((float)a_iScreenHeight);

	m_iMousePosition.x = (float)(GetMousePosition().XAxis);	//Gets the mouse's X position and converts the int to a float (scope)
	m_iMousePosition.y = (float)(GetMousePosition().YAxis); //Gets the mouse's Y position and converts the int to a float (scope)
	
	MoveSprite(m_uiTexture, m_oPosition.x, m_oPosition.y); //Moves the button to new location
	Draw();	//Calls the "Draw Function" to draw the button sprite

	if(m_iMousePosition.x >= m_oPosition.x - 125 
	&& m_iMousePosition.x <= m_oPosition.x + 125 
	&& m_iMousePosition.y >= m_oPosition.y - 25 
	&& m_iMousePosition.y <= m_oPosition.y + 25) //Checks if the mouse is on the button
	{
		m_uiTexture = m_iButtonState[1];
		m_bHovered = true;
		//Checks if the mouse is clicked
		if(GetMouseButtonDown(MOUSE_BUTTON_1))
		{
			m_uiTexture = m_iButtonState[2];	//Sets the button texture to the "Pushed" state (which is in the middle of the texture)
			m_bPushed = true;					//Sets pushed state to true
		}
		else
		{
			if(m_bPushed == true)	//Checks if the button is pushed
			{
				m_bButtonClicked = true;	//Sets the button to pushed state
			}else
			{
				m_bPushed = false;
			}
		}
	}else{
		m_bPushed = false;	//Sets button states back to default
		m_bHovered = false;	
		m_uiTexture = m_iButtonState[0];	//Sets the button texture to the "idle" state if the mouse is off the button
	}
}

void Button::Reset()
{
	m_bButtonClicked = false; //Sets button click state back to default
	m_bPushed = false;
}

void Button::Draw()
{
	DrawSprite(m_uiTexture);	//Draws the button texture that's passed into the class
}

bool Button::ButtonClicked()
{
	return m_bButtonClicked;	//Returns the button's clicked state
}
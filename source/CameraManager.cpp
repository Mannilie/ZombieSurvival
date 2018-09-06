#include "CameraManager.h"

CameraManager::CameraManager(){}
CameraManager::~CameraManager(){}

CameraManager::CameraManager(Point2D a_oVelocity, Point2D a_oPosition)
{
	m_oVelocity = a_oVelocity;	//Sets the camera's velocity to the one passed into the class
	m_oPosition = a_oPosition;	//Sets the camera's position to the one passed into the class
	m_iMoveTimer= 0;	//Initialises the timer
}

void CameraManager::MainMenuCamera()
{	
	if(m_iMoveTimer >= 100)	//Checks if the timer has incremented to 100 frames (framework)
	{
		if(m_oPosition.x + 900 >= GetMapDimensions() || m_oPosition.x <= 0)	//Checks if the camera has hit the boundaries of the map along the X axis
		{
			m_oVelocity.x = m_oVelocity.x *-1;	//Inverts the velocity's value to move the camera along the opposite X direction
		}
		if(m_oPosition.y + 900 >= GetMapDimensions() || m_oPosition.y <= 0) //Checks if the camera has hit the boundaries of the map along the Y axis
		{
			m_oVelocity.y = m_oVelocity.y *-1;	//Inverts the velocity's value to move the camera along the opposite Y direction
		}
		m_iMoveTimer = 0;	//Resets the timer
		m_oPosition.x += m_oVelocity.x;	//Sets the new position of the camera
		m_oPosition.y += m_oVelocity.y;
	}
	m_iMoveTimer++;	//Incremements the timer
	MoveCamera(m_oPosition.x, m_oPosition.y);	//Moves the camera
}


void CameraManager::AdjustCamera(Point2D a_oPlayerPosition, const int a_iScreenWidth, const int a_iScreenHeight, const int a_iMapDimension) //void function to check if the camera has gone past certain collisions of the map
{
	m_fMapDimension = (float) a_iMapDimension; //Converts the map dimensions to a float
	if(a_oPlayerPosition.x <= 450 && a_oPlayerPosition.y <= 450){ //Checks if camera is in top-left corner of screen
		MoveCamera (0, 0);
	}else if(a_oPlayerPosition.x >= a_iMapDimension - 450 && a_oPlayerPosition.y <= 450){ //Checks if camera is in top-right corner of screen
		MoveCamera (m_fMapDimension - 900, 0);
	}else if(a_oPlayerPosition.x <= 450 && a_oPlayerPosition.y >= a_iMapDimension - 450){ //Checks if camera is in bottom-left corner of screen
		MoveCamera (0, m_fMapDimension - 900);
	}else if(a_oPlayerPosition.x >= a_iMapDimension - 450 && a_oPlayerPosition.y >= a_iMapDimension - 450){ //Checks if camera is in bottom-right corner of screen
		MoveCamera (m_fMapDimension - 900, m_fMapDimension - 900);
	}else if(a_oPlayerPosition.x >= a_iMapDimension - 450 && a_oPlayerPosition.y <= a_iMapDimension - 450){ //Checks if camera is on the right-hand side of the screen
		MoveCamera (m_fMapDimension - 900, a_oPlayerPosition.y - (a_iScreenWidth /2)); //Only moves camera along Y Axis
	}else if(a_oPlayerPosition.x <= 450 && a_oPlayerPosition.y >= 450){ //Checks if camera is on the left-hand side of the screen
		MoveCamera (0, a_oPlayerPosition.y - (a_iScreenWidth /2)); //Only moves camera along Y Axis
	}else if(a_oPlayerPosition.x >= 450 && a_oPlayerPosition.y <= 450){ //Checks if camera is on the top of the screen
		MoveCamera (a_oPlayerPosition.x - (a_iScreenWidth / 2) , 0); //Only moves camera along X Axis
	}else if(a_oPlayerPosition.x <= m_fMapDimension - 450 && a_oPlayerPosition.y >= m_fMapDimension - 450){ //Checks if camera is on the bottom of the screen
		MoveCamera (a_oPlayerPosition.x - (a_iScreenWidth /2), m_fMapDimension - 900);  //Only moves camera along X Axis
	}else{
		MoveCamera (a_oPlayerPosition.x - (a_iScreenWidth / 2), a_oPlayerPosition.y - (a_iScreenWidth /2)); //Moves the camera relative to player position
	}
}
////////////////////////////////////////////////////////////
// File: CameraManager.h
// Author: Emmanuel Vaccaro
// Date: 15/03/2014
// Brief: Used for handling camera entity features.
////////////////////////////////////////////////////////////
#ifndef __CAMERAMANAGER_H__
#define __CAMERAMANAGER_H__

#include "GameObject.h"

class CameraManager : public GameObject	//Inherits GameObject class
{
private:
	int m_iMoveTimer;		//Used as a timer to move the camera at set intervals
	float m_fMapDimension;	//Used to store the map dimension obtained from "GameObject"
public:
	CameraManager();	//Default constructor
	~CameraManager();	//Default deconstructor
	CameraManager(Point2D a_oVelocity, Point2D a_oPosition);	//Custom constructor
	void AdjustCamera(Point2D a_oPlayerPosition, const int a_iScreenWidth, const int a_iScreenHeight, const int a_iMapDimension); //void function used to move the camera relative to the player
	void MainMenuCamera();	//void function used to move the main menu's camera
};

#endif //__CAMERAMANAGER_H__
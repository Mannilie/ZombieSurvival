#include "GameObject.h"

GameObject::GameObject(){}
GameObject::~GameObject(){}

Point2D GameObject::GetMousePosition()
{
	GetMouseLocation(m_iMousePosition.XAxis, m_iMousePosition.YAxis);	//Gets the mouse location as an int
	GetCameraPosition(m_fCamX, m_fCamY);	//Gets the camera position as a float
	m_iMousePosition.XAxis += (int)m_fCamX;	//Adds the camera  position to the mouse location for calculation and converts camera location to int
	m_iMousePosition.YAxis += (int)m_fCamY;
	return m_iMousePosition;//Returns the new mouse position
}

const float GameObject::GetPI()
{
	const float PI = 3.1415926535897f;	//Used as constant integer for the PI
	return PI;	//Returns the const float PI
}
const int GameObject::GetMapDimensions()
{
	const int iMapDimension = 1800;	//Sets the constant int of map dimensions
	return iMapDimension; //Returns the const int map dimensions
}

const int GameObject::GetScreenWidth()
{
	const int iScreenWidth	= 900;	//Sets the constant int of screen width
	return iScreenWidth;	//Returns the const int screen width
}

const int GameObject::GetScreenHeight()
{
	const int iScreenHeight	= 900;	//Sets the constant int of screen height
	return iScreenHeight;	//Returns the const int screen height
}

const int GameObject::GetZombieAmount()
{
	const int iZombieAmount = 10;	//Sets the constant int of zombie amount
	return iZombieAmount;	//Returns the const int zombie amount
}
////////////////////////////////////////////////////////////
// File: Button.h
// Author: Emmanuel Vaccaro
// Date: 10/03/2014
// Brief: Used to create buttons on the screen.
////////////////////////////////////////////////////////////
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Textures.h"
#include "GameObject.h"

class Button : public GameObject, public Textures	//Multiple inheritance - Inherits both GameObject and Textures
{
private:
	unsigned int m_iButtonState[3];	//Declares a char array pointer Used to store the different button states
	const char* ButtonTexture;		//Used to store the button texture that is passed into the class
	Point2D m_oMousePosition;		//Used to obtain the mouse position and store it into each button
	bool m_bHovered;			
	bool m_bPushed;					//Used to consist of button states
	bool m_bButtonClicked;
public:
	Button();	//Default constructor
	~Button();	//Default deconstructor
	Button(const char* a_cButtonTexture, int a_iWidth, int a_iHeight, Point2D a_oPosition);	//Custom constructor
	void Update(const int a_iScreenWidth, const int a_iScreenHeight);	//Update function
	bool ButtonClicked();	//ButtonClicked function used to check if the button has been clicked
	void GetTexture();		//GetTexture funcion used to obtain the modified texture using "Textures" header class
	void Draw();			//Draw function
	void Reset();			//Reset function used to set all class objects (variables) to default
};

#endif // __BUTTON_H__
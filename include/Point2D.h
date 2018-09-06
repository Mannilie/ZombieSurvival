////////////////////////////////////////////////////////////
// File: Point2D.h
// Author: Emmanuel Vaccaro
// Date: 8/03/2014
// Brief: Used for allocating sprite locations
////////////////////////////////////////////////////////////
#ifndef __POINT2D_H__
#define __POINT2D_H__

#include "AIE.h"

struct Point2D
{
	float x;			//Stores the X location
	float y;			//Stores the Y location
	int XAxis, YAxis;	//Stores the CALCULATED X and Y locations
	
	Point2D() {x = 0; y = 0; XAxis = 0; YAxis = 0;}	//Initialises Point2D floats

	Point2D(float x, float y) //Creates a function able to be used to set x and y explicitly
	{
		this->x = x;	//Returns x
		this->y = y;	//Returns y
	}
};

#endif // __POINT2D_H__
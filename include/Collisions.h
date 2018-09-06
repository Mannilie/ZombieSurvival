#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

#include "Point2D.h"
#include <math.h>

class Collisions
{
protected:
	Point2D m_oPosition;
	Point2D Top;
	Point2D Bottom;
	bool CollisionDetected;
public:
	Collisions();
	Collisions(Point2D a_oPosition);
	~Collisions();
	virtual void Update(Point2D a_oPosition) = 0;
	virtual bool CheckForCollisions(Point2D a_oPosition) = 0;
};

#endif
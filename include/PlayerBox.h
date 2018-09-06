#ifndef __PLAYERBOX_H__
#define __PLAYERBOX_H__

#include "Collisions.h"

class PlayerBox : public Collisions
{
private:
	int m_iWidth;
	int m_iHeight;
public:
	PlayerBox();
	PlayerBox(int a_iWidth, int a_iHeight, Point2D a_oPosition);
	~PlayerBox();
	virtual void Update(Point2D a_oPosition);
	virtual bool CheckForCollisions(Point2D a_oPosition);
};

#endif
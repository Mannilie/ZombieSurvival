#ifndef __ZOMBIEBOX_H__
#define __ZOMBIEBOX_H__

#include "Collisions.h"

class ZombieBox : public Collisions
{
private:
	int m_iWidth;
	int m_iHeight;
public:
	ZombieBox();
	ZombieBox(int a_iWidth, int a_iHeight, Point2D a_oPosition);
	~ZombieBox();
	virtual void Update(Point2D a_oPosition);
	virtual bool CheckForCollisions(Point2D a_oPosition);
};

#endif
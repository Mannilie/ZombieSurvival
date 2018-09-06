#include "ZombieBox.h"

ZombieBox::ZombieBox(){}
ZombieBox::ZombieBox(int a_iWidth, int a_iHeight, Point2D a_oPosition)
{
	this->m_iWidth		= a_iWidth;
	this->m_iHeight		= a_iHeight;
	this->m_oPosition	= a_oPosition;
}
ZombieBox::~ZombieBox(){}

void ZombieBox::Update(Point2D a_oPosition) 
{
	this->m_oPosition = a_oPosition;
}

bool ZombieBox::CheckForCollisions(Point2D a_oPosition)
{
	if(a_oPosition.x >= m_oPosition.x - m_iWidth / 2 
	&& a_oPosition.x <= m_oPosition.x + m_iWidth / 2
	&& a_oPosition.y >= m_oPosition.y - m_iHeight / 2
	&& a_oPosition.y <= m_oPosition.y + m_iHeight / 2)
	{
		CollisionDetected = true;
	}
	else
	{
		CollisionDetected = false;
	}
	return CollisionDetected;
}
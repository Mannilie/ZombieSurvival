#include "Collisions.h"

Collisions::Collisions()
{
	CollisionDetected = false;
}
Collisions::Collisions(Point2D a_oPosition)
{
	this->m_oPosition = a_oPosition;
}
Collisions::~Collisions()
{

}
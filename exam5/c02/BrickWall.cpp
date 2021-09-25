#include "BrickWall.hpp"

BrickWall::BrickWall() : ATarget("Inconspicuous Red-brick Wall")
{
	return;
}

BrickWall::~BrickWall()
{
	return;
}
	
BrickWall* BrickWall::clone() const
{
	return new BrickWall();
}


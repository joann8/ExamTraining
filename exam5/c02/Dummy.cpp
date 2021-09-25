#include "Dummy.hpp"

Dummy::Dummy() : ATarget("Target Practice Dummy")
{
	return;
}

Dummy::~Dummy()
{
	return;
}
	
Dummy* Dummy::clone() const
{
	return new Dummy();
}


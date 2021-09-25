#include "Fwoosh.hpp"

Fwoosh::Fwoosh() : ASpell("Fwoosh", "fwooshed")
{
	return;
}

Fwoosh::~Fwoosh()
{
	return;
}
	
Fwoosh* Fwoosh::clone() const
{
	return new Fwoosh();
}


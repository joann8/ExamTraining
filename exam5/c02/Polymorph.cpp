#include "Polymorph.hpp"

Polymorph::Polymorph() : ASpell("Polymorph", "turned into a critter")
{
	return;
}

Polymorph::~Polymorph()
{
	return;
}
	
Polymorph* Polymorph::clone() const
{
	return new Polymorph();
}


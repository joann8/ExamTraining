#include "Fireball.hpp"

Fireball::Fireball() : ASpell("Fireball", "burnt to a crisp")
{
	return;
}

Fireball::~Fireball()
{
	return;
}
	
Fireball* Fireball::clone() const
{
	return new Fireball();
}


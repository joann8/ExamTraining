#include "ASpell.hpp"
ASpell::ASpell() : name("no name"), effects("no effects")
{
	return;
}


ASpell::ASpell(std::string name, std::string effects) : name(name), effects(effects)
{
	return;
}

ASpell::~ASpell()
{
	return;
}
	
ASpell::ASpell(ASpell const& src)
{
	name = src.getName();
	effects = src.getEffects();
}

ASpell& ASpell::operator=(ASpell const& src)
{
	name = src.getName();
	effects = src.getEffects();
	return *this;
}
		
std::string const& ASpell::getName() const
{
	return name;
}

std::string const& ASpell::getEffects() const
{
	return effects;
}

void ASpell::launch(ATarget const& target) // const?
{
	target.getHitBySpell(*this);
}

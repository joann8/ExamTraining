#include "ATarget.hpp"

ATarget::ATarget() : type("typeless target")
{
	return;
}

ATarget::ATarget(std::string type) : type(type)
{
	return;
}

ATarget::~ATarget()
{
	return;
}
	
ATarget::ATarget(ATarget const& src)  
{
	type = src.getType();
}

ATarget& ATarget::operator=(ATarget const& src)
{
	type = src.getType();
	return *this;
}
		
std::string const& ATarget::getType() const
{
	return type;
}

void ATarget::getHitBySpell(ASpell const& spell) const
{
	std::cout << type << " has been " << spell.getEffects() << "!" << std::endl;
}


#ifndef Fireball_hpp
#define Fireball_hpp

#include "ASpell.hpp"

class Fireball : public ASpell
{
	public:
		Fireball();
		virtual ~Fireball();
	
		Fireball* clone() const;

};

#endif

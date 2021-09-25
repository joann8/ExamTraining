#ifndef Fwoosh_hpp
#define Fwoosh_hpp

#include "ASpell.hpp"

class Fwoosh : public ASpell
{
	public:
		Fwoosh();
		virtual ~Fwoosh();
	
		Fwoosh* clone() const;

};

#endif

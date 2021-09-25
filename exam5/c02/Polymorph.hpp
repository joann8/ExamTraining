#ifndef Polymorph_hpp
#define Polymorph_hpp

#include "ASpell.hpp"

class Polymorph : public ASpell
{
	public:
		Polymorph();
		virtual ~Polymorph();
	
		Polymorph* clone() const;

};

#endif

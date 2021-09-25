#ifndef Dummy_hpp
#define Dummy_hpp

#include "ATarget.hpp"

class Dummy : public ATarget
{
	public:
		Dummy();
		virtual ~Dummy();
	
		Dummy* clone() const;

};

#endif

#ifndef ATarget_hpp
#define ATarget_hpp

#include <string>
#include <iostream>
#include "ASpell.hpp"

class ASpell;

class ATarget
{
	public:
		ATarget();
		ATarget(std::string type); // const &
		virtual ~ATarget();
	
		ATarget(ATarget const& src);
		ATarget& operator=(ATarget const& src);
		
		std::string const& getType() const;

		virtual ATarget* clone() const = 0;

		void getHitBySpell(ASpell const& spell) const;


	private:
		std::string type; 

};

#endif

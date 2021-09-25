#ifndef ASpell_hpp
#define ASpell_hpp

#include <string>
#include <iostream>
#include "ATarget.hpp"

class ATarget;

class ASpell
{
	public:
		ASpell();
		ASpell(std::string name, std::string effects);
		virtual ~ASpell();
	
		ASpell(ASpell const& src);
		ASpell& operator=(ASpell const& src);
		
		std::string const& getName() const;
		std::string const& getEffects() const;

		virtual ASpell* clone() const = 0;

		void launch(ATarget const& target);


	private:
		std::string name;
		std::string effects;

};

#endif

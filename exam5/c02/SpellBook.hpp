#ifndef SpellBook_hpp
#define SpellBook_hpp

#include <string>
#include <iostream>
#include <vector>
#include "ATarget.hpp"

class SpellBook
{
	public:
		SpellBook();
		~SpellBook();

		void learnSpell(ASpell* src);
		void forgetSpell(std::string const& spell_name);
		ASpell* createSpell(std::string const& spell_name);

	private:
		SpellBook(SpellBook const& src);
		SpellBook& operator=(SpellBook const& src);
		std::vector<ASpell*> spell_book;

};

#endif

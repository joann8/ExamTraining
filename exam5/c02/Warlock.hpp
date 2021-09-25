#ifndef Warlock_hpp
#define Warlock_hpp

#include <string>
#include <iostream>
#include <vector>
#include "ATarget.hpp"
#include "ASpell.hpp"
#include "SpellBook.hpp"

class Warlock
{
	public:
		Warlock(std::string name, std::string title);
		~Warlock();

		std::string const& getName() const;
		std::string const& getTitle() const;

		void setTitle(std::string const & src);

		void introduce() const;

		void learnSpell(ASpell* src);
		void forgetSpell(std::string spell_name);
		void launchSpell(std::string spell_name, ATarget & target);

	private:
		Warlock();
		Warlock(Warlock const& src);
		Warlock& operator=(Warlock const& src);
		std::string name;
		std::string title;
		SpellBook spell_book;

};

#endif

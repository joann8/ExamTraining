#include "SpellBook.hpp"

SpellBook::SpellBook()
{
	return;
}

SpellBook::~SpellBook()
{
	std::vector<ASpell*>::iterator it = spell_book.begin();
	std::vector<ASpell*>::iterator ite = spell_book.end();

	while (it != ite)
	{
		delete (*it);
		it++;
	}
	return;
}


void SpellBook::learnSpell(ASpell* src)
{
	std::vector<ASpell*>::iterator it = spell_book.begin();
	std::vector<ASpell*>::iterator ite = spell_book.end();

	if (src == NULL)
		return;
	while (it != ite)
	{
		if ((*it)->getName() == src->getName())
			return;
		it++;
	}
	spell_book.push_back(src->clone());
	return;
}
		
		
void SpellBook::forgetSpell(std::string const& spell_name)
{
	std::vector<ASpell*>::iterator it = spell_book.begin();
	std::vector<ASpell*>::iterator ite = spell_book.end();

	while (it != ite)
	{
		if ((*it)->getName() == spell_name)
		{
			delete (*it);
			spell_book.erase(it);
			return;
		}
		it++;
	}
	return;
}


ASpell* SpellBook::createSpell(std::string const& spell_name)
{
	std::vector<ASpell*>::iterator it = spell_book.begin();
	std::vector<ASpell*>::iterator ite = spell_book.end();

	while (it != ite)
	{
		if ((*it)->getName() == spell_name)
		{
			return (*it);
		}
		it++;
	}
	return NULL;
}


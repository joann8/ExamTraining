#include "Warlock.hpp"

Warlock::Warlock(std::string name, std::string title) : name(name), title(title)
{
	std::cout << this->name << ": This looks like another boring day." << std::endl;
	return;
}

Warlock::~Warlock()
{
	std::cout << this->name << ": My job here is done!" << std::endl;
	std::vector<ASpell*>::iterator it = spell_book.begin();
	std::vector<ASpell*>::iterator ite = spell_book.end();

	while (it != ite)
	{
		delete (*it);
		spell_book.erase(it);
		it++;
	}
	//clear a rajouter?
	return;
}


std::string const& Warlock::getName() const
{
	return this->name;
}

std::string const& Warlock::getTitle() const
{
	return this->title;
}

void Warlock::setTitle(std::string const & src)
{
	this->title = src;
}

void Warlock::introduce() const
{
	std::cout << name << ": I am " << name << ", " << title << "!" << std::endl;
}

void Warlock::learnSpell(ASpell *src)
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

void Warlock::forgetSpell(std::string spell_name)
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

void Warlock::launchSpell(std::string spell_name, ATarget & target)
{
	std::vector<ASpell*>::iterator it = spell_book.begin();
	std::vector<ASpell*>::iterator ite = spell_book.end();

	while (it != ite)
	{
		if ((*it)->getName() == spell_name)
		{
			(*it)->launch(target);
			//target.getHitBySpell(*(*it));
			return;
		}
		it++;
	}
	return;
}

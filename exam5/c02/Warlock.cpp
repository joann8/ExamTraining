#include "Warlock.hpp"

Warlock::Warlock(std::string name, std::string title) : name(name), title(title)
{
	std::cout << this->name << ": This looks like another boring day." << std::endl;
	return;
}

Warlock::~Warlock()
{
	std::cout << this->name << ": My job here is done!" << std::endl;
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
	spell_book.learnSpell(src);
}

void Warlock::forgetSpell(std::string spell_name)
{
	spell_book.forgetSpell(spell_name);
}

void Warlock::launchSpell(std::string spell_name, ATarget & target)
{
	ASpell* tmp = spell_book.createSpell(spell_name);
	if (tmp != NULL)
		tmp->launch(target);
	return;
}

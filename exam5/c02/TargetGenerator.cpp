#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator()
{
	return;
}

TargetGenerator::~TargetGenerator()
{
	std::vector<ATarget*>::iterator it = target_list.begin();
	std::vector<ATarget*>::iterator ite = target_list.end();

	while (it != ite)
	{
		delete (*it);
		it++;
	}
	//clear a rajouter?
	return;
}


void TargetGenerator::learnTargetType(ATarget *src)
{
	std::vector<ATarget*>::iterator it = target_list.begin();
	std::vector<ATarget*>::iterator ite = target_list.end();

	if (src == NULL)
		return;
	while (it != ite)
	{
		if ((*it)->getType() == src->getType())
			return;
		it++;
	}
	target_list.push_back(src->clone());
	return;
}

void TargetGenerator::forgetTargetType(std::string const& target_name)
{
	std::vector<ATarget*>::iterator it = target_list.begin();
	std::vector<ATarget*>::iterator ite = target_list.end();

	while (it != ite)
	{
		if ((*it)->getType() == target_name)
		{
			delete (*it);
			target_list.erase(it);
			return;
		}
		it++;
	}
	return;
}

ATarget* TargetGenerator::createTarget(std::string const& target_name)
{
	std::vector<ATarget*>::iterator it = target_list.begin();
	std::vector<ATarget*>::iterator ite = target_list.end();

	while (it != ite)
	{
		if ((*it)->getType() == target_name)
		{
			return (*it);
		}
		it++;
	}
	return NULL;
}

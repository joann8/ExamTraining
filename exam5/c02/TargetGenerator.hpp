#ifndef TargetGenerator_hpp
#define TargetGenerator_hpp

#include <string>
#include <iostream>
#include <vector>
#include "ATarget.hpp"

class TargetGenerator
{
	public:
		TargetGenerator();
		TargetGenerator(std::string type); // const &
		virtual ~TargetGenerator();
		
		void learnTargetType(ATarget* src);
		void forgetTargetType(std::string const& target_name);
		ATarget* createTarget(std::string const& target_name);	


	private:
		TargetGenerator(TargetGenerator const& src);
		TargetGenerator& operator=(TargetGenerator const& src);
		std::vector<ATarget*> target_list;


};

#endif

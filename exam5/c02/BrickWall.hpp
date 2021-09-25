#ifndef BrickWall_hpp
#define BrickWall_hpp

#include "ATarget.hpp"

class BrickWall : public ATarget
{
	public:
		BrickWall();
		virtual ~BrickWall();
	
		BrickWall* clone() const;

};

#endif

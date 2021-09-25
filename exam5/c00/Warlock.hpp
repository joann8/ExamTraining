#ifndef Warlock_hpp
#define Warlock_hpp

#include <string>
#include <iostream>

class Warlock
{
	public:
		Warlock(std::string name, std::string title); // std::string const& name, std::string const& title
		~Warlock();

		std::string const& getName() const;
		std::string const& getTitle() const;

		void setTitle(std::string const & src);

		void introduce() const;

	private:
		Warlock();
		Warlock(Warlock const& src);
		Warlock& operator=(Warlock const& src);
		std::string name;
		std::string title;

};

#endif

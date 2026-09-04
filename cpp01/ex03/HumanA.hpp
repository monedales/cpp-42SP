#ifndef HUMAN_A_HPP
#define HUMAN_A_HPP
#include <string>
#include "Weapon.hpp"


class HumanA
{
	private:
	const Weapon &weapon;
		std::string name;
	public:
        HumanA(const Weapon &weapon, const std::string &name);
		~HumanA();
		void    attack(void);
};

#endif

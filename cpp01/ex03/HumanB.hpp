#ifndef HUMAN_B_HPP
#define HUMAN_B_HPP
#include <string>
#include "Weapon.hpp"


class HumanB
{
	private:
		std::string name;
        Weapon *weapon;
	public:
        HumanB(const std::string &name);
		~HumanB();
		void    attack(void);
        void    setWeapon(Weapon *weapon);
};

#endif

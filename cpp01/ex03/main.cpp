#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"
#include <iostream>


int main(void)
{
	{
		Weapon club = Weapon("crude spiked club");
		HumanA vamp1(club, "Louis");
		vamp1.attack();
		club.setType("some other type of club");
		vamp1.attack();
	}
	{
		Weapon club = Weapon("crude spiked club");
		HumanB vamp2("Claudia");
		vamp2.attack();
		club.setType("some other type of club");
		vamp2.attack();
	}
	{
		Weapon club = Weapon("crude spiked club");
		HumanB vamp3("Lestat");
		vamp3.setWeapon(&club);
		vamp3.attack();
		club.setType("some other type of club");
		vamp3.attack();
	}
	std::cout << "No stake or sunlight needed, eternity itself is the only weapon that never misses" << std::endl;
	return (0);
}

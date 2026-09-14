#include "ClapTrap.hpp"
#include "ScavTrap.hpp"


int main(void)
{
	std::cout << "\n*** Test 1: Default constructor ***\n";
	{
		ScavTrap dScav;
		std::cout << "dScav"; 
		dScav.takeDamage(50);
		std::cout << "-- se sobrou 50 de vida, prova que começou com 100 (nao 10) --\n";
	}

	std::cout << "\n*** Test 2: Named constructor (valores sobrescritos) ***\n";
	{
		ScavTrap louis("Louis");
		louis.takeDamage(50);
		std::cout << "-- se sobrou 50 de vida, prova que começou com 100 (nao 10) --\n";
	}

	std::cout << "\n*** Test 3: Copy constructor (encadeamento) ***\n";
	{
		ScavTrap original("Lestat");
		ScavTrap copy(original);
	}

	std::cout << "\n*** Test 4: Copy assignment operator ***\n";
	{
		ScavTrap claudia("Claudia");
		ScavTrap armand("Armand");
		armand = claudia;
	}

	std::cout << "\n*** Test 5: métodos herdados (takeDamage/beRepaired) ***\n";
	{
		ScavTrap gabrielle("Gabrielle");
		gabrielle.takeDamage(30);
		gabrielle.beRepaired(10);
	}

	std::cout << "\n*** Test 6: attack() sobrescrito ***\n";
	{
		ScavTrap marius("Marius");
		marius.attack("a fledgling vampire");
	}

	std::cout << "\n*** Test 7: guardGate() ***\n";
	{
		ScavTrap david("David");
		david.guardGate();
	}

	return (0);
}

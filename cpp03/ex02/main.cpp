#include "ClapTrap.hpp"
#include "FragTrap.hpp"


int main(void)
{
	std::cout << "\n*** Test 1: Default constructor ***\n";
	{
		FragTrap dFrag;
	}

	std::cout << "\n*** Test 2: Named constructor (valores sobrescritos) ***\n";
	{
		FragTrap jesse("Jesse");
		jesse.takeDamage(70);
		std::cout << "-- se sobrou 30 de vida, prova que comecou com 100 --\n";
	}

	std::cout << "\n*** Test 3: Copy constructor (encadeamento) ***\n";
	{
		FragTrap original("Maharet");
		FragTrap copy(original);
	}

	std::cout << "\n*** Test 4: Copy assignment operator ***\n";
	{
		FragTrap mekare("Mekare");
		FragTrap santino("Santino");
		santino = mekare;
	}

	std::cout << "\n*** Test 5: metodos herdados (attack/takeDamage/beRepaired) ***\n";
	{
		FragTrap khayman("Khayman");
		khayman.attack("a mortal");
		khayman.takeDamage(40);
		khayman.beRepaired(10);
	}

	std::cout << "\n*** Test 6: highFivesGuys() ***\n";
	{
		FragTrap eric("Eric");
		eric.highFivesGuys();
	}

	std::cout << "\n*** Test 7: energyPoints (100) chega a 0 ***\n";
	{
		FragTrap sybelle("Sybelle");
		for (int i = 0; i < 100; i++)
			sybelle.attack("a training dummy");
		std::cout << "-- energia deveria estar zerada agora, esse ataque tem que falhar --\n";
		sybelle.attack("Benji");
	}

	return (0);
}

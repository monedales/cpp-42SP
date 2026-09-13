#include "ClapTrap.hpp"


int main(void)
{
	std::cout << "\n*** Test 1: Default constructor ***\n";
	{
		ClapTrap dTrap;
		dTrap.attack("a bat");
	}

	std::cout << "\n*** Test 2: Parameter constructor ***\n";
	{
		ClapTrap pTrap("Louis");
		pTrap.attack("Lestat");
	}

	std::cout << "\n*** Test 3: Copy constructor ***\n";
	{
		ClapTrap original("Lestat");
		ClapTrap copy(original);
		copy.attack("a rat");
	}

	std::cout << "\n*** Test 4: Copy assignment operator ***\n";
	{
		ClapTrap claudia("Claudia");
		ClapTrap armand("Armand");
		armand = claudia;
		armand.attack("Marius");
	}

	std::cout << "\n*** Test 5: takeDamage (com clamp em 0) ***\n";
	{
		ClapTrap gabrielle("Gabrielle");
		gabrielle.takeDamage(3);
		gabrielle.takeDamage(4);
		std::cout << "-- agora um dano maior que a vida restante, pra testar o clamp --\n";
		gabrielle.takeDamage(100);
	}

	std::cout << "\n*** Test 6: beRepaired ***\n";
	{
		ClapTrap daniel("Daniel");
		daniel.takeDamage(6);
		daniel.beRepaired(2);
	}

	std::cout << "\n*** Test 7: energyPoints chega a 0 ***\n";
	{
		ClapTrap akasha("Akasha");
		for (int i = 0; i < 10; i++)
			akasha.attack("a cultist");
		std::cout << "-- energia deveria estar zerada agora, esse ataque tem que falhar --\n";
		akasha.attack("Enkil");
	}

	std::cout << "\n*** Test 8: hitPoints chega a 0 ***\n";
	{
		ClapTrap pandora("Pandora");
		pandora.takeDamage(50);
		std::cout << "-- vida deveria estar zerada agora, attack e beRepaired tem que falhar --\n";
		pandora.attack("Marius");
		pandora.beRepaired(5);
	}

	return (0);
}

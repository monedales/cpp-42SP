#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP
#include <iostream>
#include <string>


# define RED "\e[0;31m"
# define LILAC "\033[38;2;200;162;200m"
# define PEACH "\033[38;2;255;190;150m"
# define RESET "\e[0m"
# define PURPLE "\e[4;36m"


class	ClapTrap
{
protected:
	std::string		name;
	unsigned int	hitPoints;
	unsigned int	energyPoints;
	unsigned int	attackDamage;

public:
	ClapTrap();
    ClapTrap(const std::string &name);
	ClapTrap(const ClapTrap &obj);
	~ClapTrap();
	ClapTrap& operator=(const ClapTrap &obj);

	void	attack(const std::string &target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
};

#endif

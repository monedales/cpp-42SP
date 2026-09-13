#include <iostream>
#include <string>
#include "FragTrap.hpp"
#include "ClapTrap.hpp"


FragTrap::FragTrap() : ClapTrap()
{
    std::cout << LILAC << "Default FragTrap constructor called" << RESET << std::endl;
}

FragTrap::FragTrap(const FragTrap &obj) : ClapTrap(obj)
{
    std::cout << LILAC << "Copy constructor for FragTrap " << this->name << " called" << RESET << std::endl;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name)
{
    this->hitPoints = 100;
    this->energyPoints = 100;
    this->attackDamage = 30;
    std::cout << LILAC << "Initializated constructor for FragTrap " << this->name <<  " called" << RESET << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &obj)
{
    if (this != &obj)
    {
		this->name = obj.name;
        this->hitPoints = obj.hitPoints;
        this->energyPoints = obj.energyPoints;
        this->attackDamage = obj.attackDamage;
    }
    std::cout << LILAC << "Copy assignment operator for FragTrap " << this->name << " called" << RESET << std::endl;
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << LILAC << "Destructor for FragTrap " << this->name << " called" << RESET << std::endl;
}

void FragTrap::highFivesGuys(void)
{
    std::cout << PURPLE << "FragTrap " << this->name << " is giving hi five, guys!" << RESET << std::endl;
}

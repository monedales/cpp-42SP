#include <iostream>
#include <string>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"


ScavTrap::ScavTrap() : ClapTrap()
{
    std::cout << LILAC << "Default ScavTrap constructor called" << RESET << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &obj) : ClapTrap(obj)
{
    std::cout << LILAC << "Copy constructor for ScavTrap " << this->name << " called" << RESET << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
{
    this->hitPoints = 100;
    this->energyPoints = 50;
    this->attackDamage = 20;
    std::cout << LILAC << "Initializated constructor for ScavTrap " << this->name <<  " called" << RESET << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &obj)
{
    if (this != &obj)
    {
		this->name = obj.name;
        this->hitPoints = obj.hitPoints;
        this->energyPoints = obj.energyPoints;
        this->attackDamage = obj.attackDamage;
    }
    std::cout << LILAC << "Copy assignment operator for ScavTrap " << this->name << " called" << RESET << std::endl;
	return (*this);
}

ScavTrap::~ScavTrap()
{
	std::cout << LILAC << "Destructor for ScavTrap " << this->name << " called" << RESET << std::endl;
}

void ScavTrap::guardGate(void)
{
    std::cout << PURPLE << "ScavTrap " << this->name << " is now in Gate keeper mode!" << RESET << std::endl;
}

void   ScavTrap::attack(const std::string &target)
{
    if (this->hitPoints == 0)
        std::cout << PEACH << "ScavTrap " << this->name  << " has no hit points left!" << RESET <<  std::endl;
    else if (this->energyPoints == 0)
        std::cout << PEACH << "ScavTrap " << this->name  << " has not enough energy points!" << RESET <<  std::endl;
    else
    {
        std::cout << RED << "ScavTrap " << this->name  << " attacks "  << target << ", causing " << this->attackDamage << " points of damage!" << RESET << std::endl;
        this->energyPoints--;
    }
}

#include "ClapTrap.hpp"


ClapTrap::ClapTrap(): hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << LILAC << "Default ClapTrap constructor called" << RESET << std::endl;
}

ClapTrap::ClapTrap(const std::string &name): name(name), hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << LILAC << "String constructor for " << this->name <<  " called" << RESET << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &obj)
{
    *this = obj;
    std::cout << LILAC << "Copy constructor for " << this->name << " called" << RESET << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << LILAC << "Destructor for " << this->name << " called" << RESET << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &obj)
{
    if (this != &obj)
    {
		this->name = obj.name;
        this->hitPoints = obj.hitPoints;
        this->energyPoints = obj.energyPoints;
        this->attackDamage = obj.attackDamage;
    }
    std::cout << LILAC << "Copy assignment operator for " << this->name << " called" << RESET << std::endl;
	return (*this);
}

void   ClapTrap::attack(const std::string &target)
{
    if (this->hitPoints == 0)
        std::cout << PEACH << this->name  << " has no hit points left!" << RESET <<  std::endl;
    else if (this->energyPoints == 0)
        std::cout << PEACH << this->name  << " has not enough energy points!" << RESET <<  std::endl;
    else
    {
        std::cout << RED << this->name  << " attacks "  << target << ", causing " << this->attackDamage << " points of damage!" << RESET << std::endl;
        this->energyPoints--;
    }
}

void   ClapTrap::takeDamage(unsigned int amount)
{
    if (this->hitPoints < amount)
		this->hitPoints = 0;
	else
		this->hitPoints -= amount;
	std::cout << RED << this->name << " took " << amount << " points of damage, being left with "
		<< this->hitPoints << " hit points." << RESET << std::endl;
}

void   ClapTrap::beRepaired(unsigned int amount)
{
    if (this->hitPoints == 0)
        std::cout << PEACH << this->name << " has not enough hit points to be repaired!" << RESET << std::endl;
    else if (this->energyPoints == 0)
        std::cout << PEACH << this->name << " has not enough energy points!" << RESET << std::endl;
    else
    {
        this->hitPoints += amount;
        this->energyPoints--;
        std::cout << PURPLE << this->name << " is repaired for " << amount
            << " hit points, now at " << this->hitPoints << " hit points!" << RESET << std::endl;
    }
}

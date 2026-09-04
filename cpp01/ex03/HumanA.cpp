#include "Weapon.hpp"
#include "HumanA.hpp"
#include <iostream>


HumanA::HumanA(const Weapon &weapon, const std::string &name) : weapon(weapon), name(name) {}

HumanA::~HumanA() {}

void    HumanA::attack(void)
{
    std::cout << this->name << " attacks with their " << weapon.getType() << std::endl;
}

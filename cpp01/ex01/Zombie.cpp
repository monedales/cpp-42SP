#include "Zombie.hpp"
#include <iostream>


Zombie::Zombie() {}

Zombie::~Zombie()
{
    std::cout << "Die, die, my darling " << this->name << std::endl;
}

void    Zombie::announce(void)
{
    std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void    Zombie::setName(const std::string &name)
{
    this->name = name;
}

#include "Zombie.hpp"
#include <iostream>


Zombie::Zombie(const std::string &name) : name(name) {}

Zombie::~Zombie()
{
    std::cout << "Die, die, my darling " << this->name << std::endl;
}

void    Zombie::announce(void)
{
    std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

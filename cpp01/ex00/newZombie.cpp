#include "Zombie.hpp"


Zombie* newZombie(const std::string &name)
{
    Zombie* zombs = new Zombie(name);
    return (zombs);
}

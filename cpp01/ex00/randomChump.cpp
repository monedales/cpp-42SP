#include "Zombie.hpp"


void 	randomChump(const std::string &name)
{
    Zombie zombs(name);
    zombs.announce();
}

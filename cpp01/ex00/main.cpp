#include <iostream>
#include <string>
#include "Zombie.hpp"


int main(void)
{
    Zombie *zombs;
    zombs = new Zombie("Heap's Zombie");
    zombs->announce();
    randomChump("Stack's Zombie");
    delete(zombs);
    return (0);
}

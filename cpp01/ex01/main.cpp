#include <iostream>
#include <string>
#include "Zombie.hpp"


int main(void)
{
    Zombie *horde;

    int num = 5;
    std::string zombieName = "haldebaran";
    horde = zombieHorde(num, zombieName);
    for (int i = 0; i < num; i++)
        horde[i].announce();
    delete[](horde);
    return (0);
}

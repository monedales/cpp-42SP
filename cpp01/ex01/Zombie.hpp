#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <string>


class Zombie
{
    private:
		std::string name;
	public:
        Zombie();
        ~Zombie();
		void 	announce(void);
        void    setName(const std::string &name);
};

Zombie* zombieHorde(int N, std::string name);

#endif

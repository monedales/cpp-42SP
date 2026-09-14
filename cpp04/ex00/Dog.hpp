#ifndef DOG_HPP
#define DOG_HPP
#include "Animal.hpp"

# define GOLD "\033[38;2;255;180;60m"
# define CYAN "\033[38;2;120;220;255m"


class	Dog : public Animal
{
public:
	Dog();
	Dog(const Dog &obj);
	Dog &operator=(const Dog &obj);
	~Dog();

	void	makeSound() const;
};

#endif

#include "WrongAnimal.hpp"


WrongAnimal::WrongAnimal(): type("WrongAnimal")
{
	std::cout << MAGENTA << "WrongAnimal default constructor called" << RESET << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &obj)
{
	*this = obj;
	std::cout << MAGENTA << "WrongAnimal copy constructor called" << RESET << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &obj)
{
	if (this != &obj)
		this->type = obj.type;
	std::cout << MAGENTA << "WrongAnimal copy assignment operator called" << RESET << std::endl;
	return (*this);
}

WrongAnimal::~WrongAnimal()
{
	std::cout << MAGENTA << "WrongAnimal destructor called" << RESET << std::endl;
}

std::string const &WrongAnimal::getType() const
{
	return (this->type);
}

void	WrongAnimal::makeSound() const
{
	std::cout << "...🎤🐟" << std::endl;
}

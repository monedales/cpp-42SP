#include "Animal.hpp"


Animal::Animal(): type("Animal")
{
	std::cout << LILAC << "Animal default constructor called" << RESET << std::endl;
}

Animal::Animal(const Animal &obj)
{
	*this = obj;
	std::cout << LILAC << "Animal copy constructor called" << RESET << std::endl;
}

Animal &Animal::operator=(const Animal &obj)
{
	if (this != &obj)
		this->type = obj.type;
	std::cout << LILAC << "Animal copy assignment operator called" << RESET << std::endl;
	return (*this);
}

Animal::~Animal()
{
	std::cout << LILAC << "Animal destructor called" << RESET << std::endl;
}

std::string const &Animal::getType() const
{
	return (this->type);
}

void	Animal::makeSound() const
{
	std::cout << "...🎤" << std::endl;
}

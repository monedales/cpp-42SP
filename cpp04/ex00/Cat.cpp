#include "Cat.hpp"


Cat::Cat()
{
	this->type = "Cat";
	std::cout << PINK << "Cat default constructor called" << RESET << std::endl;
}

Cat::Cat(const Cat &obj): Animal(obj)
{
	std::cout << PINK << "Cat copy constructor called" << RESET << std::endl;
}

Cat &Cat::operator=(const Cat &obj)
{
	if (this != &obj)
		Animal::operator=(obj);
	std::cout << PINK << "Cat copy assignment operator called" << RESET << std::endl;
	return (*this);
}

Cat::~Cat()
{
	std::cout << PINK << "Cat destructor called" << RESET << std::endl;
}

void	Cat::makeSound() const
{
	std::cout << PEACH << "Meow!" << RESET << std::endl;
}

#include "Dog.hpp"


Dog::Dog()
{
	this->type = "Dog";
	std::cout << CYAN << "Dog default constructor called" << RESET << std::endl;
}

Dog::Dog(const Dog &obj): Animal(obj)
{
	std::cout << CYAN << "Dog copy constructor called" << RESET << std::endl;
}

Dog &Dog::operator=(const Dog &obj)
{
	if (this != &obj)
		Animal::operator=(obj);
	std::cout << CYAN << "Dog copy assignment operator called" << RESET << std::endl;
	return (*this);
}

Dog::~Dog()
{
	std::cout << CYAN << "Dog destructor called" << RESET << std::endl;
}

void	Dog::makeSound() const
{
	std::cout << GOLD << "Woof! Woof!" << RESET << std::endl;
}

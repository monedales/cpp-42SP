#include "Dog.hpp"


Dog::Dog()
{
	this->type = "Dog";
    this->brain = new Brain(); 
	std::cout << CYAN << "Dog default constructor called" << RESET << std::endl;
}

Dog::Dog(const Dog &obj): Animal(obj)
{
    this->brain = new Brain(*obj.brain);
	std::cout << CYAN << "Dog copy constructor called" << RESET << std::endl;
}

Dog &Dog::operator=(const Dog &obj)
{
	if (this != &obj)
    {
		Animal::operator=(obj);
        delete this->brain;
		this->brain = new Brain(*obj.brain);
    }
	std::cout << CYAN << "Dog copy assignment operator called" << RESET << std::endl;
	return (*this);
}

Dog::~Dog()
{
    delete this->brain;
	std::cout << CYAN << "Dog destructor called" << RESET << std::endl;
}

void	Dog::makeSound() const
{
	std::cout << GOLD << "Woof! Woof!" << RESET << std::endl;
}

Brain	*Dog::getBrain() const
{
	return (this->brain);
}

#include "Cat.hpp"


Cat::Cat()
{
	this->type = "Cat";
    this->brain = new Brain(); 
	std::cout << PEACH << "Cat default constructor called" << RESET << std::endl;
}

Cat::Cat(const Cat &obj): Animal(obj)
{
    this->brain = new Brain(*obj.brain);
	std::cout << PEACH << "Cat copy constructor called" << RESET << std::endl;
}

Cat &Cat::operator=(const Cat &obj)
{
	if (this != &obj)
    {
		Animal::operator=(obj);
        delete this->brain;
		this->brain = new Brain(*obj.brain);
    }
	std::cout << PEACH << "Cat copy assignment operator called" << RESET << std::endl;
	return (*this);
}

Cat::~Cat()
{
    delete this->brain;
	std::cout << PEACH << "Cat destructor called" << RESET << std::endl;
}

void	Cat::makeSound() const
{
	std::cout << PINK << "Meow!" << RESET << std::endl;
}

Brain	*Cat::getBrain() const
{
	return (this->brain);
}

#include "WrongCat.hpp"


WrongCat::WrongCat(): WrongAnimal()
{
	this->type = "WrongCat";
	std::cout << MINT << "WrongCat default constructor called" << RESET << std::endl;
}

WrongCat::WrongCat(const WrongCat &obj): WrongAnimal(obj)
{
	std::cout << MINT << "WrongCat copy constructor called" << RESET << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &obj)
{
	if (this != &obj)
		WrongAnimal::operator=(obj);
	std::cout << MINT << "WrongCat copy assignment operator called" << RESET << std::endl;
	return (*this);
}

WrongCat::~WrongCat()
{
	std::cout << MINT << "WrongCat destructor called" << RESET << std::endl;
}

void	WrongCat::makeSound() const
{
	std::cout << RED << "Meow! (nunca deveria aparecer via WrongAnimal*)" << RESET << std::endl;
}

#include "Brain.hpp"


Brain::Brain()
{
	std::cout << MINT << "Brain default constructor called" << RESET << std::endl;
}

Brain::Brain(const Brain &obj)
{
	*this = obj;
	std::cout << MINT << "Brain copy constructor called" << RESET << std::endl;
}

Brain &Brain::operator=(const Brain &obj)
{
	if (this != &obj)
	{
		for (int i = 0; i < 100; i++)
			this->ideas[i] = obj.ideas[i];
	}
	std::cout << MINT << "Brain copy assignment operator called" << RESET << std::endl;
	return (*this);
}

Brain::~Brain()
{
	std::cout << MINT << "Brain destructor called" << RESET << std::endl;
}

void	Brain::setIdea(int index, const std::string &idea)
{
	if (index < 0 || index >= 100)
		return ;
	this->ideas[index] = idea;
}

std::string const	&Brain::getIdea(int index) const
{
	static const std::string	empty = "";

	if (index < 0 || index >= 100)
		return (empty);
	return (this->ideas[index]);
}

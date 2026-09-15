#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <iostream>
#include <string>

# define LILAC "\033[38;2;200;162;200m"
# define RESET "\e[0m"


class	Animal
{
	protected:
		std::string	type;

	public:
		Animal();
		Animal(const Animal &obj);
		Animal &operator=(const Animal &obj);
		virtual ~Animal();

		std::string const	&getType() const;
		virtual void		makeSound() const = 0;
};

#endif

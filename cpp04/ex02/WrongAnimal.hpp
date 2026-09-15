#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP
#include <iostream>
#include <string>

# define MAGENTA "\033[38;2;255;80;220m"
# define RESET "\e[0m"


class	WrongAnimal
{
	protected:
		std::string	type;

	public:
		WrongAnimal();
		WrongAnimal(const WrongAnimal &obj);
		WrongAnimal &operator=(const WrongAnimal &obj);
		~WrongAnimal();

		std::string const	&getType() const;
		void		makeSound() const;
};

#endif

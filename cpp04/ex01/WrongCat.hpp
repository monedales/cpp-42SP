#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP
#include "WrongAnimal.hpp"

# define RED "\033[38;2;255;80;80m"
# define MINT "\033[38;2;150;255;200m"


class	WrongCat : public WrongAnimal
{
	public:
		WrongCat();
		WrongCat(const WrongCat &obj);
		WrongCat &operator=(const WrongCat &obj);
		~WrongCat();

		void	makeSound() const;
};

#endif

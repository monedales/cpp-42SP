#ifndef CAT_HPP
#define CAT_HPP
#include "Animal.hpp"

# define PEACH "\033[38;2;255;190;150m"
# define PINK "\033[38;2;255;105;180m"


class	Cat : public Animal
{
	public:
		Cat();
		Cat(const Cat &obj);
		Cat &operator=(const Cat &obj);
		~Cat();

		void	makeSound() const;
};

#endif

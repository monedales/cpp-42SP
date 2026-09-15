#ifndef BRAIN_HPP
#define BRAIN_HPP
#include <iostream>
#include <string>

# define MINT "\033[38;2;150;255;200m"
# define RESET "\e[0m"


class	Brain
{
	private:
		std::string	ideas[100];

	public:
		Brain();
		Brain(const Brain &obj);
		Brain &operator=(const Brain &obj);
		~Brain();

		void				setIdea(int index, const std::string &idea);
		std::string const	&getIdea(int index) const;
};

#endif

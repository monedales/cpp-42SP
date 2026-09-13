#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP
#include <string>
#include "ClapTrap.hpp"


class FragTrap : public ClapTrap
{
public:
	FragTrap();
	FragTrap(const FragTrap &obj);
	FragTrap(const std::string &name);
	FragTrap &operator=(const FragTrap &obj);
	~FragTrap();

	void	highFivesGuys(void);
};

#endif

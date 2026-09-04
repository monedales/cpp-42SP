#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <string>


class Weapon
{
	private:
		std::string type;
	public:
		Weapon(const std::string &type);
		~Weapon();
		const std::string	&getType(void) const;
		void		setType(const std::string &newType);
};

#endif

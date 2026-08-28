#include <iostream>
#include <string>
#include "PhoneBook.hpp"
#include "Colors.hpp"


static void	showMenu(void)
{
	std::cout << BOLD << LILAC << "Welcome to ✨ Mona's ✨ PhoneBook !" << RESET << "\n";
	std::cout << LILAC << "Available commands 💅🏼: \n";
	std::cout << BOLD << PINK  << "ADD"    << RESET << PEACH << "\t- Add a new contact into the phoneBook\n";
	std::cout << BOLD << MINT  << "SEARCH" << RESET << PEACH << "\t- Display the saved contacts and then search for a specific entry\n";
	std::cout << BOLD << CYAN << "EXIT"   << RESET << PEACH << "\t- Exits the program (loses all information)\n" << LILAC;
}

int main(void)
{
    PhoneBook phoneBook;
    std::string cmd;

    showMenu();
    while (true)
	{
		std::cout << "> ";
		if (!std::getline(std::cin, cmd))
			break ;
		else if (cmd == "ADD")
			phoneBook.addContact();
		else if (cmd == "SEARCH")
        {
			phoneBook.listContacts();
            phoneBook.showContact();
        }
		else if (cmd == "EXIT")
			return (0);
	}
}

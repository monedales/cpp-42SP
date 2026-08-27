#include <iostream>
#include "PhoneBook.hpp"
#include "Contact.hpp"


static void	showMenu(void)
{
	std::cout << "\033[38;2;200;162;200m Welcome to the PhoneBook Software! \033[m\n";
	std::cout << "Available commands: \n";
	std::cout << "\033[35mADD\033[m\t- Add a new contact into the phoneBook\n";
	std::cout << "\033[35mSEARCH\033[m\t- Display the saved contacts\n";
	std::cout << "\033[35mEXIT\033[m\t- Exits the program (loses all information)\n";
}

int main(void)
{
    PhoneBook phoneBook;
    // Contact contact;
    std::string cmd;

    showMenu();
    while (true)
	{
		std::cout << "> ";
		if (!std::getline(std::cin, cmd))
			break ;
		else if (cmd == "ADD")
			phoneBook.addContact();
		// else if (cmd == "SEARCH")
		// 	phoneBook.listContacts();
		else if (cmd == "EXIT")
			return (0);
	}

}
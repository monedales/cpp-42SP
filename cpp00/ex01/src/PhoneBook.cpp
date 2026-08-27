#include <iostream>
#include <iomanip>
#include <sstream>
#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
    count = 0;
}

PhoneBook::~PhoneBook() { }

std::string formatColumn(std::string value)
{
    std::ostringstream result;

    if (value.length() > 10)
        return value.substr(0, 9) + ".";
    else
    {
        result << std::right << std::setw(10) << value;
        return  result.str();
    }
}

static std::string validateField(std::string prompt)
{
    std::string value;

    std::cout << prompt;
    std::getline(std::cin, value);
    while (value.empty())
    {
        std::cout << prompt;
        std::getline(std::cin, value);
    }
    return (value);
}

void PhoneBook::addContact()
{
    Contact contact;
    std::string firstname;
    std::string lastName;
    std::string nickName;
    std::string phone;
    std::string darkestSecret;

    for (int i = 0; i < 5; i++)
    {
        switch (i)
        {
        case 0:
            firstname = validateField("Type your first name: ");
            contact.SetField(Contact::FIRST_NAME, firstname);
            break;
        case 1:
            lastName = validateField("Type your last name: ");
            contact.SetField(Contact::LAST_NAME, lastName);
            break;
        case 2:
            nickName = validateField("Type your nickname: ");
            contact.SetField(Contact::NICKNAME, nickName);
            break;
        case 3:
            phone = validateField("Type your phone number: ");
            contact.SetField(Contact::PHONE, phone);
            break;
        case 4:
            darkestSecret = validateField("Type your darkest secret 👀: ");
            contact.SetField(Contact::DARK_SECRET, darkestSecret);
            break;
        default:
            break;
        }
        
    }
    contacts[count % 8] = contact;
    count++;
}
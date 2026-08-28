#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Colors.hpp"


PhoneBook::PhoneBook()
{
    count = 0;
    validCount = 0;
}

PhoneBook::~PhoneBook() { }

static std::string formatColumn(std::string value)
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

static bool parseIndex(std::string text, int &result)
{
    std::istringstream iss(text);

    if (iss >> result && iss.eof())
        return (true);
    else
        return (false);
}

std::string PhoneBook::formatRow(int index)
{
    std::ostringstream result;
    std::string str_index;

    result << index;
    str_index = result.str();

    std::string col1 = formatColumn(str_index);
    std::string col2 = formatColumn(contacts[index].getFirstName());
    std::string col3 = formatColumn(contacts[index].getLastName());
    std::string col4 = formatColumn(contacts[index].getNickName());
    std::string row = col1 + "|" + col2 + "|" + col3 + "|" + col4;
    return (row);
}

void PhoneBook::addContact(void)
{
    Contact contact;
    std::string firstname, lastName, nickName, phone, darkestSecret;

    for (int i = 0; i < 5; i++)
    {
        switch (i)
        {
        case 0:
            firstname = validateField(BOLD + PEACH + "Type your first name: " + RESET + LILAC);
            contact.SetField(Contact::FIRST_NAME, firstname);
            break;
        case 1:
            lastName = validateField(BOLD + PEACH + "Type your last name: " + RESET + LILAC);
            contact.SetField(Contact::LAST_NAME, lastName);
            break;
        case 2:
            nickName = validateField(BOLD + PEACH + "Type your nickname: " + RESET + LILAC);
            contact.SetField(Contact::NICKNAME, nickName);
            break;
        case 3:
            phone = validateField(BOLD + PEACH + "Type your phone number: " + RESET + LILAC);
            contact.SetField(Contact::PHONE, phone);
            break;
        case 4:
            darkestSecret = validateField(BOLD + PEACH + "Type your darkest secret 👀: " + RESET + LILAC);
            contact.SetField(Contact::DARK_SECRET, darkestSecret);
            break;
        default:
            break;
        }
    }
    contacts[count % 8] = contact;
    count++;
    if (validCount < 8)
        validCount++;
}

void PhoneBook::listContacts(void)
{
    for (int i = 0; i < validCount; i++)
        std::cout << formatRow(i) << std::endl;
    std::cout << std::endl;
}

void PhoneBook::showContact(void)
{
    if (validCount <= 0)
    {
        std::cout << MAGENTA << "You don't have any contact yet, dear!" << LILAC << std::endl;
        return ;
    }
    int index;
    std::string indexText;
    bool valid = false;

    while (!valid)
    {
        indexText = validateField(BOLD + PEACH + "Type the contact's index you want to see: " + RESET + LILAC);
        if (!parseIndex(indexText, index))
            std::cout << RED << "This is not a valid input! Please type a valid number." << LILAC << std::endl;
        else if (index >= 0 && index < validCount)
        {
            valid = true;
            std::cout << contacts[index].getFirstName() << std::endl;
            std::cout << contacts[index].getLastName() << std::endl;
            std::cout << contacts[index].getNickName() << std::endl;
            std::cout << contacts[index].getPhonenumber() << std::endl;
            std::cout << contacts[index].getSecret() << std::endl;
        }
        else
            std::cout << RED << "Please type a valid number between 0 and " << validCount - 1 << "!" << LILAC << std::endl;
    }
}

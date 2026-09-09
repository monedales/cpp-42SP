#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include "Colors.hpp"

const int PhoneBook::MAX_CONTACTS;

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

static void handleInputFailure(bool &quit)
{
    if (std::cin.eof())
    {
        std::cout << "\nYOU SHALL NOT PASS! 🧙‍♂️⚔️\nstop trying to make me fail in the evaluation 👀" << std::endl;
        quit = true;
        return ;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static std::string validateField(std::string prompt, bool &quit)
{
    std::string value;

    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (std::cin.fail())
        {
            handleInputFailure(quit);
            if (quit)
                return (value);
            continue ;
        }
        if (!value.empty())
            return (value);
    }
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
    const Contact::e_field fields[5] = {Contact::FIRST_NAME, Contact::LAST_NAME, Contact::NICKNAME, Contact::PHONE, Contact::DARK_SECRET};
    const std::string questions[5] = {
        "Type your first name: ",
        "Type your last name: ",
        "Type your nickname: ",
        "Type your phone number: ",
        "Type your darkest secret 👀: "
    };
    bool quit = false;

    for (int i = 0; i < 5; i++)
    {
        std::string value = validateField(BOLD + PEACH + questions[i] + RESET + LILAC, quit);
        if (quit)
            return ;
        contact.SetField(fields[i], value);
    }
    contacts[count % MAX_CONTACTS] = contact;
    count++;
    if (validCount < MAX_CONTACTS)
        validCount++;
}

void PhoneBook::listContacts(void)
{
    std::string separator = "|";
    std::cout << BOLD << formatColumn("index") << separator 
        << formatColumn("first name") << separator 
        << formatColumn("last name") << separator 
        << formatColumn("nickname") << RESET + LILAC << std::endl;
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
    bool quit = false;

    while (!valid)
    {
        indexText = validateField(BOLD + PEACH + "Type the contact's index you want to see: " + RESET + LILAC, quit);
        if (quit)
            return ;
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

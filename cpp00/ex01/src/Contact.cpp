#include <iostream>
#include "Contact.hpp"

Contact::Contact()
{
    std::cout << "Contact Constructor called" << std::endl;
}

Contact::~Contact()
{
    std::cout << "Contact Destructor called" << std::endl;
}

void Contact::SetField(e_field field, std::string value)
{
    switch (field)
    {
    case FIRST_NAME:
        this->firstName = value;
        break;
    case LAST_NAME:
        this->lastName = value;
        break;
    case NICKNAME:
        this->nickName = value;
        break;
    case PHONE:
        this->phone = value;
        break;
    case DARK_SECRET:
        this->darkestSecret = value;
        break;
    default:
        break;
    }
}

std::string Contact::getFirstName() const
{
    return this->firstName;
}

std::string Contact::getLastName() const
{
    return this->lastName;
}

std::string Contact::getNickName() const
{
    return this->nickName;
}

std::string Contact::getPhonenumber() const
{
    return this->phone;
}

std::string Contact::getSecret() const
{
    return this->darkestSecret;
}

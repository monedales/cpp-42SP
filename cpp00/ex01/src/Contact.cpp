#include "Contact.hpp"


Contact::Contact() {}

Contact::~Contact() {}

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

std::string Contact::getFirstName(void) const
{
    return this->firstName;
}

std::string Contact::getLastName(void) const
{
    return this->lastName;
}

std::string Contact::getNickName(void) const
{
    return this->nickName;
}

std::string Contact::getPhonenumber(void) const
{
    return this->phone;
}

std::string Contact::getSecret(void) const
{
    return this->darkestSecret;
}

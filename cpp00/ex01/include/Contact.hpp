#ifndef CONTACT_H
#define CONTACT_H
#include <iostream>

class Contact
{
    private:
        std::string firstName;
        std::string lastName;
        std::string nickName;
        std::string phone;
        std::string darkestSecret;
    public:
        Contact();
        ~Contact();
};

#endif
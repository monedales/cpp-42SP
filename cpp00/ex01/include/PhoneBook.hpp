#ifndef PHONEBOOK_H
#define PHONEBOOK_H
#include "Contact.hpp"

class PhoneBook
{
    private:
        Contact contacts[8];
        int     count;
    public:
    PhoneBook();
    ~PhoneBook();
    
    void    addContact();
    
    
};
#endif
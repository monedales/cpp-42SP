#ifndef PHONEBOOK_H
#define PHONEBOOK_H
#include <string>
#include "Contact.hpp"


class PhoneBook
{
    private:
        Contact contacts[8];
        int     count;
        int     validCount;
    public:
    PhoneBook();
    ~PhoneBook();
    
    void        addContact(void);
    std::string formatRow(int index);
    void        listContacts(void);
    void        showContact(void);
};
#endif

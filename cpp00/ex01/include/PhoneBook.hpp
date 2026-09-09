#ifndef PHONEBOOK_H
#define PHONEBOOK_H
#include <string>
#include "Contact.hpp"


class PhoneBook
{
    private:
        static const int MAX_CONTACTS = 8;
        Contact contacts[MAX_CONTACTS];
        int     count;
        int     validCount;
        std::string formatRow(int index);
    public:
    PhoneBook();
    ~PhoneBook();
    
    void        addContact(void);
    void        listContacts(void);
    void        showContact(void);
};
#endif


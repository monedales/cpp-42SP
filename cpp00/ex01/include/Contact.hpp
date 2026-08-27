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
		enum	e_field
		{
			FIRST_NAME = 0,
			LAST_NAME,
			NICKNAME,
			PHONE,
			DARK_SECRET,
		};
		Contact();
		~Contact();
		void 		SetField(e_field field, std::string value);
		std::string	getFirstName() const;
		std::string getLastName() const;
		std::string getNickName() const;
		std::string	getPhonenumber() const;
		std::string	getSecret() const;
		// std::string	GetField(e_field field);
};

#endif
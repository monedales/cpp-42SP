#ifndef CONTACT_H
#define CONTACT_H
#include <string>


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
		std::string	getFirstName(void) const;
		std::string getLastName(void) const;
		std::string getNickName(void) const;
		std::string	getPhonenumber(void) const;
		std::string	getSecret(void) const;
};

#endif

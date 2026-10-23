#include <string>
#include <exception>
#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP


class   Bureaucrat
{
	private:
		const std::string   name;
		int                 grade;
	public:
		Bureaucrat();
		~Bureaucrat();
		Bureaucrat(const Bureaucrat &obj);
		Bureaucrat& operator=(const Bureaucrat &obj);     
		Bureaucrat(const std::string &name, int grade);

		const std::string	&getName() const;
		const int			&getGrade() const;
		void				incrementGrade();
		void				decrementGrade();

		class	GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class	GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

std::ostream &operator<<(std::ostream &obj, const Bureaucrat &ref);

#endif

#ifndef FORM_HPP
#define FORM_HPP

# include "Bureaucrat.hpp"
# include <string>
# include <exception>
# include <iostream>


class   Form
{
    private:
        const std::string   name;
        bool                isSigned;
        const int           signForm;
        const int           execForm;
    public:
        Form();
        ~Form();
        Form(const Form &obj);
        Form& operator=(const Form &obj);
        Form(const std::string &name, const int signForm, const int execForm);

        const std::string   &getName() const;
        bool                getIsSigned() const;
        int                 getSign() const;
        int                 getExec() const;

        void    beSigned(Bureaucrat &bur);

        class   GradeTooHighException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };
        class GradeTooLowException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };
};

std::ostream &operator<<(std::ostream &obj, const Form &ref);

#endif

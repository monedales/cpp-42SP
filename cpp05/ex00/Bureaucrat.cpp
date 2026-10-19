#include "Bureaucrat.hpp"
#include <iostream>


Bureaucrat::Bureaucrat(void)
{
    std::cout << "Default constructor called" << std::endl;
}

Bureaucrat::~Bureaucrat(void)
{
    std::cout << "Default destructor called" << std::endl;    
}

Bureaucrat::Bureaucrat(const Bureaucrat &obj) : name(obj.name), grade(obj.grade)
{
    std::cout << "Copy constructor called" << std::endl;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &obj)
{
    if (this != &obj)
        this->grade = obj.grade;
    std::cout << "Copy assignment operator for " << this->name << " called" << std::endl;
    return (*this);
}

Bureaucrat::Bureaucrat(const std::string &name, int grade): name(name), grade(1)
{
    std::cout << "Parameterized constructor called" << std::endl;
}

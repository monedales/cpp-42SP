#include "Bureaucrat.hpp"
#include <iostream>


Bureaucrat::Bureaucrat()
{
    std::cout << "Default constructor called" << std::endl;
}

Bureaucrat::~Bureaucrat()
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

Bureaucrat::Bureaucrat(const std::string &name, int grade): name(name), grade(grade)
{
    std::cout << "Parameterized constructor called" << std::endl;
    if (grade < 1)
        throw Bureaucrat::GradeTooHighException();
    else if (grade > 150)
        throw Bureaucrat::GradeTooLowException();
}

const std::string &Bureaucrat::getName() const
{
    return (this->name);
}

const int &Bureaucrat::getGrade() const
{
    return (this->grade);
}

void Bureaucrat::incrementGrade()
{
    if (this->grade <= 1)
        throw GradeTooHighException();
    else
        this->grade--;
}

void Bureaucrat::decrementGrade()
{
    if(this->grade >= 150)
        throw GradeTooLowException();
    else
        this->grade++;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
    return ("Grade too high");
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
    return ("Grade too low");
}

std::ostream &operator<<(std::ostream &obj, const Bureaucrat &ref)
{
    obj << ref.getName() << ", burocrata com classificação " << ref.getGrade() << ".";
    return (obj);
}

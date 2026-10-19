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

        const std::string &getName() const;
        const std::string &getGrade() const;
        void incrementGrade();
        void decrementGrade();

};
std::ostream &operator<<(std::ostream &obj, const Bureaucrat &ref);

#endif

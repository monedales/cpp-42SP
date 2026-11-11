#include "Bureaucrat.hpp"


int main(void)
{
    // 1) Bureaucrat válido: cria e imprime com o operator<<
    std::cout << "--- 1) bureaucrat válido ---" << std::endl;
    try
    {
        Bureaucrat mona("Mona", 42);
        std::cout << mona << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    // 2) Grade alto demais (< 1): construtor deve jogar GradeTooHigh
    std::cout << "\n--- 2) grade alto demais (0) ---" << std::endl;
    try
    {
        Bureaucrat tooHigh("Louis", 0);
        std::cout << tooHigh << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    // 3) Grade baixo demais (> 150): construtor deve jogar GradeTooLow
    std::cout << "\n--- 3) grade baixo demais (151) ---" << std::endl;
    try
    {
        Bureaucrat tooLow("Ozzy", 151);
        std::cout << tooLow << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    // 4) increment e decrement normais
    std::cout << "\n--- 4) increment / decrement normais ---" << std::endl;
    try
    {
        Bureaucrat bob("Bob", 3);
        std::cout << bob << std::endl;
        bob.incrementGrade();
        std::cout << "depois de incrementar: " << bob << std::endl;
        bob.decrementGrade();
        std::cout << "depois de decrementar 1x: " << bob << std::endl;
        bob.decrementGrade();
        std::cout << "depois de decrementar 2x: " << bob << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    // 5) Passar do limite máximo: incrementar quando já está no grade 1
    std::cout << "\n--- 5) incrementar no limite (grade 1) ---" << std::endl;
    try
    {
        Bureaucrat best("Best", 1);
        std::cout << best << std::endl;
        best.incrementGrade(); // deve jogar GradeTooHigh
        std::cout << best << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    // 6) Passar do limite mínimo: decrementar quando já está no grade 150
    std::cout << "\n--- 6) decrementar no limite (grade 150) ---" << std::endl;
    try
    {
        Bureaucrat worst("Worst", 150);
        std::cout << worst << std::endl;
        worst.decrementGrade(); // deve jogar GradeTooLow
        std::cout << worst << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return (0);
}

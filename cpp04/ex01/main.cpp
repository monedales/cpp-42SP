#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

# define LABEL "\033[2;3m"


int main()
{
	std::cout << LABEL << "--- copia profunda: Dog ---" << RESET << std::endl;
	std::cout << LABEL << "-> basic (Dog)" << RESET << std::endl;
	Dog basic;
	{
		std::cout << LABEL << "-> tmp (Dog, copy ctor de basic)" << RESET << std::endl;
		Dog tmp = basic;
		std::cout << LABEL << "-> fim do escopo interno: tmp vai ser destruido agora" << RESET << std::endl;
	}
	std::cout << LABEL << "-> basic ainda intacto (chegou ate aqui sem crash/double free)" << RESET << std::endl;

	std::cout << "\n" << LABEL << "--- copia profunda: Cat ---" << RESET << std::endl;
	std::cout << LABEL << "-> basicCat (Cat)" << RESET << std::endl;
	Cat basicCat;
	{
		std::cout << LABEL << "-> tmpCat (Cat, copy ctor de basicCat)" << RESET << std::endl;
		Cat tmpCat = basicCat;
		std::cout << LABEL << "-> fim do escopo interno: tmpCat vai ser destruido agora" << RESET << std::endl;
	}
	std::cout << LABEL << "-> basicCat ainda intacto" << RESET << std::endl;

	std::cout << "\n" << LABEL << "--- operator= tambem precisa ser deep copy ---" << RESET << std::endl;
	std::cout << LABEL << "-> dogA (Dog)" << RESET << std::endl;
	Dog dogA;
	std::cout << LABEL << "-> dogB (Dog)" << RESET << std::endl;
	Dog dogB;
	std::cout << LABEL << "-> dogB = dogA (assignment)" << RESET << std::endl;
	dogB = dogA;

	std::cout << "\n" << LABEL << "--- array misto de Animal*, deletado via Animal* ---" << RESET << std::endl;
	const int size = 4;
	Animal* animals[size];
	std::cout << LABEL << "-> criando 2 Dog + 2 Cat, guardados como Animal*" << RESET << std::endl;
	for (int i = 0; i < size / 2; i++)
		animals[i] = new Dog();
	for (int i = size / 2; i < size; i++)
		animals[i] = new Cat();
	for (int i = 0; i < size; i++)
		animals[i]->makeSound();
	std::cout << LABEL << "-> deletando o array inteiro via Animal* (destrutor precisa ser virtual)" << RESET << std::endl;
	for (int i = 0; i < size; i++)
		delete animals[i];

	return (0);
}

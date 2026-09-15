#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

# define LABEL "\033[2;3m"


int main()
{
	std::cout << LABEL << "--- Animal e abstrata ---" << RESET << std::endl;
	// Animal animalGenerico;						// nao compila: classe abstrata
	// const Animal* ponteiroGenerico = new Animal();	// nao compila: classe abstrata
	std::cout << LABEL << "-> Animal nao pode ser instanciado (descomente as linhas acima pra ver o erro)" << RESET << std::endl;

	std::cout << "\n" << LABEL << "--- Dog e Cat via Animal* ---" << RESET << std::endl;
	{
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		std::cout << j->getType() << " faz: ";
		j->makeSound();
		std::cout << i->getType() << " faz: ";
		i->makeSound();
		delete j;//should not create a leak
		delete i;
	}

	std::cout << "\n" << LABEL << "--- copia profunda: Dog ---" << RESET << std::endl;
	std::cout << LABEL << "-> basic (Dog)" << RESET << std::endl;
	Dog basic;
	basic.getBrain()->setIdea(0, "quero passear");
	{
		std::cout << LABEL << "-> tmp (Dog, copy ctor de basic)" << RESET << std::endl;
		Dog tmp = basic;
		std::cout << LABEL << "-> tmp muda a propria ideia" << RESET << std::endl;
		tmp.getBrain()->setIdea(0, "quero dormir");
		std::cout << "basic brain: " << basic.getBrain() << " | ideia 0: " << basic.getBrain()->getIdea(0) << std::endl;
		std::cout << "tmp   brain: " << tmp.getBrain() << " | ideia 0: " << tmp.getBrain()->getIdea(0) << std::endl;
		std::cout << LABEL << "-> fim do escopo interno: tmp vai ser destruido agora" << RESET << std::endl;
	}
	std::cout << LABEL << "-> basic ainda intacto (sem crash/double free)" << RESET << std::endl;
	std::cout << "basic ideia 0: " << basic.getBrain()->getIdea(0) << std::endl;

	std::cout << "\n" << LABEL << "--- copia profunda: Cat ---" << RESET << std::endl;
	std::cout << LABEL << "-> basicCat (Cat)" << RESET << std::endl;
	Cat basicCat;
	basicCat.getBrain()->setIdea(0, "quero peixe");
	{
		std::cout << LABEL << "-> tmpCat (Cat, copy ctor de basicCat)" << RESET << std::endl;
		Cat tmpCat = basicCat;
		std::cout << LABEL << "-> tmpCat muda a propria ideia" << RESET << std::endl;
		tmpCat.getBrain()->setIdea(0, "quero derrubar o copo");
		std::cout << "basicCat brain: " << basicCat.getBrain() << " | ideia 0: " << basicCat.getBrain()->getIdea(0) << std::endl;
		std::cout << "tmpCat   brain: " << tmpCat.getBrain() << " | ideia 0: " << tmpCat.getBrain()->getIdea(0) << std::endl;
		std::cout << LABEL << "-> fim do escopo interno: tmpCat vai ser destruido agora" << RESET << std::endl;
	}
	std::cout << LABEL << "-> basicCat ainda intacto" << RESET << std::endl;
	std::cout << "basicCat ideia 0: " << basicCat.getBrain()->getIdea(0) << std::endl;

	std::cout << "\n" << LABEL << "--- operator= tambem precisa ser deep copy ---" << RESET << std::endl;
	std::cout << LABEL << "-> dogA (Dog)" << RESET << std::endl;
	Dog dogA;
	dogA.getBrain()->setIdea(0, "ideia do dogA");
	std::cout << LABEL << "-> dogB (Dog)" << RESET << std::endl;
	Dog dogB;
	std::cout << LABEL << "-> dogB = dogA (assignment)" << RESET << std::endl;
	dogB = dogA;
	std::cout << LABEL << "-> depois da atribuicao: mesma ideia, brains diferentes" << RESET << std::endl;
	std::cout << "dogA brain: " << dogA.getBrain() << " | ideia 0: " << dogA.getBrain()->getIdea(0) << std::endl;
	std::cout << "dogB brain: " << dogB.getBrain() << " | ideia 0: " << dogB.getBrain()->getIdea(0) << std::endl;
	std::cout << LABEL << "-> dogB muda a propria ideia" << RESET << std::endl;
	dogB.getBrain()->setIdea(0, "ideia nova do dogB");
	std::cout << "dogA ideia 0: " << dogA.getBrain()->getIdea(0) << std::endl;
	std::cout << "dogB ideia 0: " << dogB.getBrain()->getIdea(0) << std::endl;

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

	std::cout << "\n" << LABEL << "--- fim da main: objetos da stack sendo destruidos ---" << RESET << std::endl;
	return (0);
}

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

# define LABEL "\033[2;3m"


int main()
{
	std::cout << LABEL << "-> meta (Animal)" << RESET << std::endl;
	const Animal* meta = new Animal();
	std::cout << LABEL << "-> j (Dog)" << RESET << std::endl;
	const Animal* j = new Dog();
	std::cout << LABEL << "-> i (Cat)" << RESET << std::endl;
	const Animal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();

	std::cout << "\n--- cópia e atribuição: Dog/Cat ---" << std::endl;
	std::cout << LABEL << "-> louis (Cat)" << RESET << std::endl;
	Cat louis;
	std::cout << LABEL << "-> copyLouis (Cat, copy constructor de louis)" << RESET << std::endl;
	Cat copyLouis(louis);
	std::cout << LABEL << "-> rex (Dog)" << RESET << std::endl;
	Dog rex;
	std::cout << LABEL << "-> copyRex (Dog)" << RESET << std::endl;
	Dog copyRex;
	std::cout << LABEL << "-> copyRex = rex (assignment)" << RESET << std::endl;
	copyRex = rex;

	std::cout << "\n--- delete polimórfico (Animal/Dog/Cat) ---" << std::endl;
	std::cout << LABEL << "-> delete meta" << RESET << std::endl;
	delete meta;
	std::cout << LABEL << "-> delete j" << RESET << std::endl;
	delete j;
	std::cout << LABEL << "-> delete i" << RESET << std::endl;
	delete i;

	std::cout << "\n--- WrongAnimal / WrongCat ---" << std::endl;
	std::cout << LABEL << "-> wrongMeta (WrongAnimal)" << RESET << std::endl;
	const WrongAnimal* wrongMeta = new WrongAnimal();
	std::cout << LABEL << "-> wrongCat (WrongCat, guardado como WrongAnimal*)" << RESET << std::endl;
	const WrongAnimal* wrongCat = new WrongCat();
	std::cout << LABEL << "-> wrongCat->makeSound()" << RESET << std::endl;
	wrongCat->makeSound(); // chama WrongAnimal::makeSound(), nao WrongCat::makeSound() -> nao e virtual
	std::cout << LABEL << "-> wrongMeta->makeSound()" << RESET << std::endl;
	wrongMeta->makeSound();

	std::cout << LABEL << "-> directCat (WrongCat, variavel direta)" << RESET << std::endl;
	WrongCat directCat;
	std::cout << LABEL << "-> directCat.makeSound()" << RESET << std::endl;
	directCat.makeSound(); // chamado direto no WrongCat, esse SIM chama WrongCat::makeSound()

	std::cout << LABEL << "-> copyDirectCat (WrongCat, copy constructor de directCat)" << RESET << std::endl;
	WrongCat copyDirectCat(directCat);
	std::cout << LABEL << "-> assignDirectCat (WrongCat)" << RESET << std::endl;
	WrongCat assignDirectCat;
	std::cout << LABEL << "-> assignDirectCat = directCat (assignment)" << RESET << std::endl;
	assignDirectCat = directCat;

	std::cout << LABEL << "-> delete wrongMeta" << RESET << std::endl;
	delete wrongMeta;
	std::cout << LABEL << "-> delete wrongCat" << RESET << std::endl;
	delete wrongCat;

	return (0);
}

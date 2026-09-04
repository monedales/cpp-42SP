#include <iostream>
#include <string>


int main(void)
{
    std::string string = "HI THIS IS BRAIN";
    std::string *stringPTR = &string;
	std::string &stringREF = string;

	std::cout << "O endereço de memória da variável string: " << &string << std::endl;
	std::cout << "O endereço de memória mantido por stringPTR: " << stringPTR << std::endl;
	std::cout << "O endereço de memória mantido por stringREF: " << &stringREF << std::endl;
	
	std::cout << "O valor da variável string: " << string << std::endl;
	std::cout << "O valor apontado por stringPTR: " << *stringPTR << std::endl;
	std::cout << "O valor apontado por stringREF: " << stringREF << std::endl;
    return (0);
}

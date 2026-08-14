#include <string>
#include <iostream>
#include <cctype>

class Megaphone 
{
    public:
        Megaphone() {}
        ~Megaphone() {}

    void stdoutNoise()
    {
       std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    }

    void stdoutDynamic(std::string words)
    {
        char ch;

        for (size_t i = 0; i < words.length(); i++)
        {
            ch = static_cast<char>(std::toupper(static_cast<unsigned char>(words[i])));    
            std::cout << ch;
        }
    }
};

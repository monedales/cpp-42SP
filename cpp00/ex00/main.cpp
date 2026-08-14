#include <string>
#include <iostream>
#include "Megaphone.cpp"

int main(int argc, char **argv)
{
    Megaphone megaphone;
    int i = 1;

    if (argc == 1)
    {
        megaphone.stdoutNoise();
        return (0);
    }
    while (argv[i])
    {
        megaphone.stdoutDynamic(argv[i]);
        i++;
    }
    std::cout << std::endl;

    return (0);
}
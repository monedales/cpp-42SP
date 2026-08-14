#include <string>
#include <iostream>
#include "Megaphone.cpp"

int main(int argc, char **argv)
{
    Megaphone megaphone;
    int i = 0;

    if (argc == 1)
    {
        megaphone.stdoutNoise();
        return (0);
    }
    while (argv[i + 1])
    {
        megaphone.stdoutDynamic(argv[i]);
        i++;
    }
    std::cout << std::endl;

    return (0);
}
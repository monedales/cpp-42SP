#include <iostream>
#include <fstream>
#include <string>


void replaceAll(std::string &line, const std::string &s1, const std::string &s2)
{
	size_t pos = line.find(s1, 0);
	while (pos != std::string::npos)
	{
		std::string before = line.substr(0, pos);
		std::string after = line.substr(pos + s1.length());
		line = before + s2 + after;
		pos = line.find(s1, pos + s2.length());
	}
}

int main(int argc, char **argv) 
{
	if (argc != 4 || !argv[2][0] || !argv[3][0])
	{
		std::cout << "Usage: [filename] [s1] [s2]" << std::endl;
		return (1);
	}
	std::string file = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	std::ifstream file_in(file.c_str(), std::ios::in);
	
	if (!file_in.is_open())
	{
		std::cerr << "Unable to open file." << std::endl;
		return (1);
	}
	std::ofstream file_out((file + ".replace").c_str());
	std::string line;
	while (std::getline(file_in, line))
	{
		replaceAll(line, s1, s2);
		file_out << line << std::endl;
	}
	file_in.close();
	file_out.close();
    return (0);
}

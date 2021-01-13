#include "DiskReader.h"

#include <fstream>
#include <iostream>
#include <sstream>

const bool DiskReader::ReadString(std::string& stringToFill, std::string filePath)
{
	std::stringstream stringStream;
	std::ifstream file;

	try
	{
		file.open(filePath, std::ios::in);

		if (file.fail() == false)
			stringStream << file.rdbuf();
		file.close();
		
		stringToFill = stringStream.str();
		return true;
	}
	catch (std::exception& ex)
	{
		std::cerr << "Error: Failed to read data from disk!" << std::endl;
		std::cerr << "File Path: " << filePath << std::endl;

		return false;
	}
}

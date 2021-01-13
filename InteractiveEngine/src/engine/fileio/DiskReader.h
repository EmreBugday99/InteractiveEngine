#pragma once
#include <string>

class DiskReader
{
public:
	static const bool ReadString(std::string& stringToFill, std::string filePath);
};

#include "LevelParser.hpp"

LevelParser::LevelParser(std::string p_filePath)
{
	this->filePath = p_filePath;
}

std::vector<std::vector<int>> LevelParser::parse()
{
	fileStream = new std::ifstream(this->filePath);
	std::vector<int> tempParsedString;
	std::string tempString;
	int i = 0;
	while (!fileStream->eof())
	{
		std::getline(*fileStream, tempString);
		if (tempString.length() != 0)
		{
			tempParsedString = parseString(tempString);
			parsedLevel.push_back(tempParsedString);
			i++;
		}
	}
	fileStream->close();

	return parsedLevel;
}

std::vector<int> LevelParser::parseString(std::string p_StringToParse)
{
	std::vector<int> parsedString;
	for (int i = 0; i < p_StringToParse.length(); i++)
	{
		parsedString.push_back((int)p_StringToParse[i] - '0');
	}
	return parsedString;
}
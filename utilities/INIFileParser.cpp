#include "INIFileParser.hpp"

INIFileParser::INIFileParser(std::string p_filePath)
{
	this->filePath = p_filePath;
}

std::map<std::string, std::string> INIFileParser::parse()
{
	fileStream = new std::ifstream(this->filePath);
	std::string* tempParsedString = new std::string[2];
	std::string tempString;
	while (!fileStream->eof())
	{
		std::getline(*fileStream, tempString);
		if (tempString.length() != 0)
		{
			tempParsedString = parseString(tempString);
			parsedText.insert(std::pair<std::string, std::string>(tempParsedString[0], tempParsedString[1]));
		}
	}
	fileStream->close();

	return parsedText;
}

std::string* INIFileParser::parseString(std::string p_StringToParse)
{
	std::string* parsedString = new std::string[2];
	parsedString[0] = p_StringToParse.substr(0, p_StringToParse.find(" = "));
	parsedString[0].replace(0, 1, "");
	parsedString[0].replace(parsedString[0].size()-1, 1, "");
	parsedString[1] = p_StringToParse.substr(p_StringToParse.find(" = ")+3);
	parsedString[1].replace(0, 1, "");
	parsedString[1].replace(parsedString[1].size()-1, 1, "");
	return parsedString;
}
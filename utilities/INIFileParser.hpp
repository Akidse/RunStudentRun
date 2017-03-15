#ifndef INIFILEPARSER_HPP
#define INIFILEPARSER_HPP
#include <string>
#include <map>
#include <fstream>
class INIFileParser
{
private:
	std::string filePath;
	std::ifstream* fileStream;
	std::map<std::string, std::string> parsedText;
	std::string* parseString(std::string p_StringToParse);
public:
	INIFileParser(std::string filePath);
	std::map<std::string, std::string> parse();
};
#endif
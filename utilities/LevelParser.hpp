#ifndef LEVELPARSER_HPP
#define LEVELPARSER_HPP

#include <string>
#include <vector>
#include <fstream>
class LevelParser
{
private:
	std::string filePath;
	std::ifstream* fileStream;
	std::vector<std::vector<int>> parsedLevel;
	std::vector<int> parseString(std::string p_StringToParse);
public:
	LevelParser(std::string filePath);
	void set(std::string p_key, std::string p_newval);
	void save_changes();
	std::vector<std::vector<int>> parse();
};
#endif
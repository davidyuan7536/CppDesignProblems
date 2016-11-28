#ifndef LOG_PARSER_H
#define LOG_PARSER_H

#include <string>
#include <vector>

class LogParser {
public:
	static std::string parseFile(const std::string&);
	static std::string parseLines(const std::vector < std::string >& lines);
};

#endif


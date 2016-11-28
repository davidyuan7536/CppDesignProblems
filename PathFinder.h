#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include <string>
#include <vector>

class PathFinder {
public:
	static std::vector < std::string > parseFile(const std::string&);
	static std::vector < std::string > parseLines(const std::vector < std::string >& lines);
};

#endif

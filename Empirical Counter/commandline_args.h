#ifndef EC_COMMANDLINE_ARGS
#define EC_COMMANDLINE_ARGS
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
/*
* This class is designed to handle commandline arguments, or their absence. 
*
*
*/


class commandline_args
{
private:
	std::vector<std::string> args;
public:
	commandline_args();
	~commandline_args();
	std::vector<std::string> getArgs();

};
#endif

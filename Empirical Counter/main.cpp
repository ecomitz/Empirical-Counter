#include <fstream>
#include <time.h> // used for the pursuit of an even more perfect random
#include <chrono> // used to create clocks for file names
#include <sstream> // used to create file names from clock details
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>



/*
* This program is designed to count the amount of times a certain number appears in a random generator.
* The generator will accept a range, and the program will generate a given amount of times
* The result should calculate the amount of times the chosen number appeared in the generations
* An empirical file will be created, as well, showing all generations and ran details titled at the time the test was ran
*/



using namespace std;

// Prints commandline options
void printHelp()
{
	std::cout << "-help: Prints info about the possible commands. "
		<< "For args with \"=val\", the default is that the user is prompted for it, except stated otherwise. \n" << std::endl;
	std::cout << "-nogui: bool for whether or not the program should run as a GUI (General User Interface). NYI \n" << std::endl;
	std::cout << "-lowerbound=val: Sets the lowerbound for the program. E.g: -lowerbound=4 \n" << std::endl;
	std::cout << "-upperbound=val: Sets the upperbound for the program. E.g: -upperbound=10 \n" << std::endl;
	std::cout << "-numgenerations=val: Sets the amount of generations for the program. E.g: -numgenerations=100 \n" << std::endl;
	std::cout << "-search=val: Sets the value desired for counting in the program. E.g -search=6 \n" << std::endl;
	std::cout << "-outputpath=val: Sets the location of where the output file will go. By default, this is the same folder as the program. NYI \n" << std::endl;
	std::cout << "-debug: Prints useful debugging info for fixing this program. \n" << std::endl;
}


void printDebugInfo(int argc, char* argv[])
{
	cout << "Parameters used: " << endl;
	for (int i = 0; i < argc; i++)
	{
		cout << i << ": " << argv[i] << endl;
	}


}

// Helps to construct the output file's name
void flagHelper(stringstream& builder, string& outputName)
{
	outputName = outputName + builder.str();
	builder.clear();
	builder << resetiosflags;
	builder.str("");
}
const unsigned char SWITCH_COUNT = 8; // The amount of possibly used commandline options
enum COMMAND_LINE_OPTIONS { HELP, NOGUI, LOWERBOUND, UPPERBOUND, NUMGENERATIONS, SEARCH, OUTPUTPATH, DEBUG };
int main(int argc, char* argv[])
{



	// The variables of the program. Pre initialized to avoid warnings

	bool* switches = new bool[SWITCH_COUNT]; // used to determine whether or not commandline args were used. See readme for numbering
	ofstream output;
	int search = 5; // The value of which occurrances we are interested in counting
	int lowerBound = 0;
	int upperBound = 10;
	unsigned int occurrances = 0; // The amount of times search occurred in generation. Set to zero initially because no instances have occurred yet empirically. 
	int cur = 0; // When we loop the generator, this will refer to the number being currently generated.
	int numOfGenerations = 100;
	vector<string> args;
	//----------------------------------------------------------------------------------------------------------------------------------------
		// Switch reading section

		// Step 1: Set default values for switches
		// Step 2: Read the passed arguments
		// Step 3: Parse the passed arguments
		// Step 3a: Turn on the switches from the arguments
		// Step 3b: Process the data from arguments with data

	for (unsigned char i = 0; i < SWITCH_COUNT; i++)
	{
		switches[i] = false;
	}


	for (int i = 0; i < argc; i++)
	{
		args.push_back(argv[i]);
	}


	for (const string& arg : args)
	{
		string val = "";
		if (arg == "-help" && switches[HELP] == false)
		{
			printHelp();
			switches[HELP] = true;
			return 0;
		}

		if (arg.rfind("-nogui", 0) == 0)
		{
			switches[NOGUI] = true;
		}
		if (arg.rfind("-lowerbound=", 0) == 0)
		{
			switches[LOWERBOUND] = true;
			val = arg.substr(12);
			lowerBound = stoi(val);
		}
		if (arg.rfind("-upperbound=", 0) == 0)
		{
			switches[UPPERBOUND] = true;
			val = arg.substr(12);
			upperBound = stoi(val);
		}
		if (arg.rfind("-numgenerations=", 0) == 0)
		{
			switches[NUMGENERATIONS] = true;
			val = arg.substr(16);
			numOfGenerations = stoi(val);
		}
		if (arg.rfind("-search=", 0) == 0)
		{
			switches[SEARCH] = true;
			val = arg.substr(8);
			search = stoi(val);

		}
		if (arg.rfind("-outputpath", 0) == 0)
		{
			switches[OUTPUTPATH] = true;
		}
		if (arg == "-debug")
		{
			switches[DEBUG] = true;
			printDebugInfo(argc, argv);
		}

	}








	//----------------------------------------------------------------------------------------------------------------------------------------
		// Section for settings of generation
		// Step 1: Ask for settings
		// Step 2: Check settings for validity
	if (switches[SEARCH] == false)
	{
		cout << "What number are you interested in counting the occurances of?" << endl;
		cin >> search;
	}
	if (switches[LOWERBOUND] == false)
	{
		cout << "And what shall be your lower bound?" << endl;
		cin >> lowerBound;
	}
	if (switches[UPPERBOUND] == false)
	{
		cout << "And what shall be your upper bound?" << endl;
		cin >> upperBound;
	}
	if (switches[NUMGENERATIONS] == false)
	{
		cout << "Finally, how many generations do you want?" << endl;
		cin >> numOfGenerations;
	}

	// Section for incase lowerBound or upperBound is greater than search target
	while (search < lowerBound || search > upperBound)
	{
		if (search > upperBound)
		{
			cout << "Please select a new upperbound; you are looking for a number greater than it." << endl;
			cin >> upperBound;
		}
		if (search < lowerBound)
		{
			cout << "Please select a new lowerbound; you are looking for a number less than it." << endl;
			cin >> lowerBound;
		}
	}
//----------------------------------------------------------------------------------------------------------------------------------------
	// Section for constructing file
	// Step 1: Find out what time and day it is
	// Step 2: Parse that data into a stringstream to make the file name
	// Step 3: Create the file

	chrono::system_clock::time_point clockTime = chrono::system_clock::now();
	const time_t printableTime = chrono::system_clock::to_time_t(clockTime);
	tm ltm;
	localtime_s(&ltm, &printableTime);
	stringstream builder;
	string outputName = "";
	builder << setw(2) << setfill('0') << ltm.tm_mon + 1;
	flagHelper(builder, outputName);
	builder << '-' << setw(2) << setfill('0') << ltm.tm_mday;
	flagHelper(builder, outputName);
	builder << "-" << ltm.tm_year + 1900;
	flagHelper(builder, outputName);
	builder << "_" << setw(2) << setfill('0') << ltm.tm_hour;
	flagHelper(builder, outputName);
	builder << "-" << setw(2) << setfill('0') << ltm.tm_min;
	flagHelper(builder, outputName);
	builder << "-" << setw(2) << setfill('0') << ltm.tm_sec << ".txt";
	outputName = outputName + builder.str();	
	output.open(outputName);

//----------------------------------------------------------------------------------------------------------------------------------------
	// Section for running the generations
	// Step 1: Set the seed
	// Step 2: Print the settings to the output file
	// Step 3: Randomly generate numbers and count the occurrances of targeted number (search)

	time_t* seed = 0;
	srand(time(seed)); // helps to make an even more truly random number generator
	output << "Search target: " << search << endl;
	output << "Lower bound: " << lowerBound << endl;
	output << "Upper bound: " << upperBound << endl;
	output << "Number of generations: " << numOfGenerations << endl;
	cout << "Generating..." << endl;
	for (unsigned int i = 1; i <= numOfGenerations; i++) // i set to 1 so generations can be cut into lines of 10 
	{
		
		cur = rand() % (upperBound - lowerBound + 1) + lowerBound; 
		if (search == cur)
		{
			occurrances++;
		}
		cout << cur << " ";
		output << cur << " ";
		if (i % 10 == 0)
		{
			cout << endl;
			output << endl;
		}
	}

	cout << "There were: " << occurrances << " occurrances of " << search;
	output << "There were: " << occurrances << " occurrances of " << search;
	
	output.close();


	return 0;
}
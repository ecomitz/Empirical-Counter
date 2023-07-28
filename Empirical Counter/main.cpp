#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h> // used for the pursuit of an even more perfect random
#include <string>
#include <chrono> // used to create clocks for file names
#include <sstream> // used to create file names from clock details




/*
* This program is designed to count the amount of times a certain number appears in a random generator.
* The generator will accept a range, and the program will generate a given amount of times
* The result should calculate the amount of times the chosen number appeared in the generations
* An empirical file will be created, as well, showing all generations and ran details titled at the time the test was ran
*/



using namespace std;


// Helps to construct the output file's name
void flagHelper(stringstream& builder, string& outputName)
{
	outputName = outputName + builder.str();
	builder.clear();
	builder << resetiosflags;
	builder.str("");
}


int main()
{
	// The variables of the program
	ofstream output;
	int search; // The value of which occurrances we are interested in counting
	int lowerBound; 
	int upperBound;
	unsigned int occurrances = 0; // The amount of times search occurred in generation. Set to zero initially because no instances have occurred yet empirically. 
	int cur; // When we loop the generator, this will refer to the number being currently generated.
	int numOfGenerations;

//----------------------------------------------------------------------------------------------------------------------------------------
	// Section for settings of generation
	// Step 1: Ask for settings
	// Step 2: Check settings for validity

	cout << "What number are you interested in counting the occurances of?" << endl;
	cin >> search;
	cout << "And what shall be your lower bound?" << endl;
	cin >> lowerBound;
	cout << "And what shall be your upper bound?" << endl;
	cin >> upperBound;
	cout << "Finally, how many generations do you want?" << endl;
	cin >> numOfGenerations;

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
	for (int i = 1; i <= numOfGenerations; i++) // i set to 1 so generations can be cut into lines of 10 
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
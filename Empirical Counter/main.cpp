#include <iostream>
#include <fstream>
#include <time.h> // used for the pursuit of an even more perfect random

using namespace std;
/*
* This program is designed to count the amount of times a certain number appears in a random generator.
* The generator will accept a range, and the program will generate a given amount of times
* The result should calculate the amount of times the chosen number appeared in the generations
* An empirical file will be created, as well, showing all generations
*/
int main()
{
	// The variables of the program
	ofstream output;
	int search; // The value of whomst occurrances we are interested in counting
	int lowerBound; 
	int upperBound;
	unsigned int occurrances = 0; // Set to zero because no instances have occurred yet empirically. 
	int cur; // When we loop the generator, this will refer to the number being currently generated.
	int numOfGenerations;

//----------------------------------------------------------------------------------------------------------------------------------------
	cout << "What number are you interested in counting the occurances of?" << endl;
	cin >> search;
	cout << "And what shall be your lower bound?" << endl;
	cin >> lowerBound;
	cout << "And what shall be your upper bound?" << endl;
	cin >> upperBound;
	cout << "Finally, how many generation do you want?" << endl;
	cin >> numOfGenerations;
	/* Note: If the lower bound provided is lower than the search value, it is not possible to find.
	* There are multiple ways to handle such a problem
	* We could automatically set the lower bound to be equal to the search value
	* or we could ask for a different search value or lower bound value
	* Some error handling may come in handy here. NYI.
	*/

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

	output.open("output.txt");
	srand(time(NULL)); // helps to make an even more truly random number generator
	cout << "Generating..." << endl;
	for (int i = 0; i < numOfGenerations; i++)
	{
		
		cur = rand() % (upperBound - lowerBound + 1) + lowerBound; // This is still imperfect; it apparently favors lower numbers
		if (search == cur)
		{
			occurrances++;
		}
		cout << cur << endl;
		output << cur << endl;
	}
	cout << "There were: " << occurrances << " occurrances of " << search;
	output.close();


	return 0;
}
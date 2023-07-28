import random
from datetime import datetime

# This program is designed to count the amount of times a certain number appears in a random generator.
# The generator will accept a range, and the program will generate a given amount of times
# The result should calculate the amount of times the chosen number appeared in the generations
# An empirical file will be created, as well, showing all generations and ran details titled at the time the test was ran


##----------------------------------------------------------------------------------------------------------------------------------------
# Section for setting up variables and settings for generator
# Step 1: Ask for settings
# Step 2: Check settings for validity

occurrances = 0
print("What number are you interested in counting the occurrances of?")
search = int(input())
print("And what shall be your lower bound?")
lowerBound = int(input())
print("And what shall be your upper bound?")
upperBound = int(input())
print("Finally, how many generations do you want?")
numOfGenerations = int(input())

while(search < lowerBound or search > upperBound):
    if search > upperBound:
        print("Please select a new upperbound; you are looking for a number greater than it.")
        upperBound = int(input())
    if search < lowerBound:
        print("Please select a new lowerbound; you are looking for a number less than it.")
        lowerBound = int(input())


##----------------------------------------------------------------------------------------------------------------------------------------
# Section for constructing file
# Step 1: Find out what time and day it is
# Step 2: Parse that data into a stringstream to make the file name
# Step 3: Create the file


curTime = datetime.now()
dateAndTime = curTime.strftime("%m-%d-%Y_%H-%M-%S")
fileName = dateAndTime + ".txt"
f = open(fileName, "a")


##----------------------------------------------------------------------------------------------------------------------------------------
# Section for running the generations
# Step 1: Print the settings to the output file
# Step 2: Randomly generate numbers and count the occurrances of targeted number (search)


f.write("Search target: " + str(search) + '\n')
f.write("Lower bound: " + str(lowerBound) + '\n')
f.write("Upper bound: " + str(upperBound) + '\n')
f.write("Number of generations: " + str(numOfGenerations) + '\n')


print("Generating...")
for x in range(1, numOfGenerations + 1):  # Range set to 1 to numOfGenerations + 1 to allow for splitting of lines of 10
    cur = random.randint(lowerBound, upperBound)
    if(cur == search):
        occurrances = occurrances + 1
    print(cur, end=", ")
    f.write(str(cur) + ", ")
    if(x % 10 == 0):
        print("\n")
        f.write("\n")
    

print("There were: " + str(occurrances) + " occurrances of " + str(search))
f.write("There were: " + str(occurrances) + " occurrances of " + str(search))
    
f.close()

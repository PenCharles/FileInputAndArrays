#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
using namespace std;

//global constants
const int MAX_ARRAY = 1000;
//const string MY_FILE = "parkingfees.txt";

//function prototypes
double LowestCharge (double array[], int arrayCount);
double HighestCharge (double array[], int arrayCount);
double AverageCharge (double array[], int arrayCount);
void OpenAndCheckFile (ifstream& input);
void ResultsDisplay (double array[], int arrayCount, string parkingType);
void ProcessArrays (ifstream& input, double arrayC [], double arrayU [],
					int& countC, int& countU);

int main ()
{
	//local variable
	int covCount = 0;					//holds value for covered[] bounds checking
	int uncCount = 0;					//holds value for uncovered[] bounds checking
	ifstream inData;					//file stream variable for inputting data
	double covered[MAX_ARRAY];			//an array holding charges for each vehicle in covered
	double uncovered[MAX_ARRAY];		//an array holding charges for each vehicle in uncovered
	string uncoveredPark = "uncovered";	//to display the different parking types
	string coveredPark = "covered";		//to display the different parking types
	string filename = "parkingfees.txt";//name of the only file to use
	
	cout << "This program will determine the lowest, highest and average charge "
		 << "of all uncovered and covered parking customers." << endl << endl;
	
	inData.open(filename.c_str());
		 
	OpenAndCheckFile (inData);
		 
	if (inData)
	{
		ProcessArrays (inData, covered, uncovered, covCount, uncCount);
		ResultsDisplay (uncovered, uncCount, uncoveredPark);
		ResultsDisplay (covered, covCount, coveredPark);
		inData.close ();
	}
	else
	{
		return 1;
	}
	
 	cout << endl << endl;
 	return 0;
}

double LowestCharge (double array[], int arrayCount)
{
	int lowestIndex = 0; //will element loc of lowest charge
	int index;			 //initial var for FOR
	double lowest;		 //lowest charge in the array
	
	//loops through array to find lowest charge
	for (index = 1; index < arrayCount; index++)
		if (array[lowestIndex] > array[index])
			lowestIndex = index;
			
	lowest = array[lowestIndex];
			
	return lowest;
}

double HighestCharge (double array[], int arrayCount)
{
	int maxIndex = 0; 	 //will element loc of highest charge
	int index;			 //initial var for FOR
	double highest;		//highest charge in the array
	
	//loops through array to find highest charge
	for (index = 1; index < arrayCount; index++)
		if (array[maxIndex] < array[index])
			maxIndex = index;
			
	highest = array[maxIndex];
	
	return highest;
}

double AverageCharge (double array[], int arrayCount)
{
	double sum = 0; 	//holds total value of charges
	double average;		//holds the average of the charges
	int index;			//initial var for FOR
	
	//loops through entire array summing the charges
	for (index = 0; index < arrayCount; index++)
		sum = sum + array[index];
		
	average = sum / arrayCount; //calc average
	
	return average;
}

void ResultsDisplay (double array[], int arrayCount, string parkingType)
{
	
	if (arrayCount != 0)
	{
		cout << "For " << arrayCount << " " << parkingType << " "
		     << "parking customers:" << endl;	
		cout << setprecision(2) << showpoint << fixed;
		//display lowest charge
		cout << setw(26) << "Lowest charge is $" << setw(8)
		     << LowestCharge (array, arrayCount) << endl;
		//display Highest charge     
		cout << setw(26) << "Highest charge is $" << setw(8)
		     << HighestCharge (array, arrayCount) << endl;
		//display Average charge
		cout << setw(26) << "Average charge is $" << setw(8)
		     << AverageCharge (array, arrayCount) << endl << endl;
	} 
	else
	{
		cout << "There were NO " << parkingType << " parking customers."
			 << endl << endl;	
	}

}

void OpenAndCheckFile (ifstream& input)
{
	if (!input)			//if..else tests to see if file exists
	{
		cout << endl << "This file does not exist. "
		   	         << "The program terminates.";
	}
}

void ProcessArrays (ifstream& input, double arrayC [], double arrayU [],
					int& countC, int& countU)
{
	char parkingType;			//uncovered or covered parking var
	double fee;					//parking fee for each user
	
	//priming read
	input >> parkingType;
	input >> fee;
	
	//input fee var into proper array based on "parkingType" var
	if (parkingType == 'U')
	{
		arrayU[countU] = fee; //input fee car into uncov array
		countU++;		 //increment uncovered parking count
	}
	else
	{
		arrayC[countC] = fee;	//add fee to the cov parking array;
		countC++;			//increment covered parking count
	}
	
	//looping through the rest of the data in the file
	while (input >> parkingType)	//testing for end of file
	{
		//input >> parkingType;
		input >> fee;
		
		if (parkingType == 'U')
		{
			if (countU <= MAX_ARRAY) //if uncov parking reaches limit ignore the rest
			{
				arrayU[countU] = fee;	//add the fee var to array
				countU++;			//increment uncovered parking count
			}
			else
				cout << "Too much uncovered parking data in file" << endl << endl;	
		}
		else
		{
			if (countC <= MAX_ARRAY) //if cov parking reaches limit ignore the rest
			{
				arrayC[countC] = fee;	//add fee var to array
				countC++;			//increment covered parking count
			}
			else
				cout << "Too much covered parking data in file" << endl << endl;	
		}
	}
}

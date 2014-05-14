// Central Limit Theorem Calculator
// Alex Mun, Steve Briceno
// ECE 2524: Unix
//
// The Central Limit Theorem Calculator accepts as inputs:
// 1.) Sample Size
// 2.) Sample Data
// 3.) Confidence Level
// 4.) Standard Deviation
//
// The CLT Calculator will output:
// 1.) Sample Mean
// 2.) Sample Variance
// 3.) Error Margin
// 4.) Confidence Interval
//
// Assumptions made by the CLT Calculator:
// 1.) It is up to the user to specify a sufficiently large sample size
// 2.) Confidence levels will only be chosen among 90%, 95%, or 99%

#include <iostream>
#include <stdio.h>
#include <vector>
#include <numeric>
#include <math.h>
#include <cctype> 
#include <string>
#include <cstdlib>
using namespace std;

// Advanced error checking for inputs that conform to a specific failure condition
double inputIdentifier()
{
	bool error = false;		// False indicates there are no issues with input
	double input = 0;
	cin >> input;
	if(input < 0)			// Inputs must not be negative values
	{
		cin.clear();
		while(cin.get()!='\n');
		error = true;
	}
	else if(cin.fail() || cin.get()!='\n')	// Inputs must be double values
    {
        cin.clear();
        while(cin.get()!='\n');
		error = true;
    }
	if(error == true)
	{
		return -1;			// Error condition
	}
	else
	{
		return input;
	}
}

// Prompts the user for the sample size and performs error checking
int sampleSizeGenerator()
{
	string input;
	int tempInt = 0;
	cout << "Enter Sample Size: ";
	getline(cin, input);
	tempInt = atoi(input.c_str());
	while(tempInt <= 0)
	{
		cout << endl << "Invalid Input. Enter Sample Size: ";
		cin.clear();
		input = "";
		getline(cin, input);
		tempInt = atoi(input.c_str());
	}
	return atoi(input.c_str());
}

// Prompts the user for sample data entries and performs error checking
void addSampleData(vector<double> &sample, int sampleSize)
{
	double input;
	for(int n = 0; n < sampleSize; n++)
	{
		cout << "Enter Data for Sample " << n+1 << ": ";
		input = inputIdentifier();
		while(input == -1)
		{
			cout << endl << "Invalid Input. Enter Data for Sample " << n+1 << ": ";
			input = inputIdentifier();
		}
		sample[n] = input;
	}
}

// Prompts the user for the standard deviation and performs error checking
int stanDevGenerator()
{
	string input;
	int tempInt = 0;
	cout << "Enter Standard Deviation: ";
	getline(cin, input);
	tempInt = atoi(input.c_str());
	while(tempInt <= 0)
	{
		cout << endl << "Invalid Input. Enter Standard Deviation: ";
		cin.clear();
		input = "";
		getline(cin, input);
		tempInt = atoi(input.c_str());
	}
	return atoi(input.c_str());
}

// Error checking for malformed confidence level inputs
int clvlErrorHandling()
{
	int confidenceLevel = 0;
	cout << "Invalid Input. Select a Confidence Level" << endl;
	cout << "90%" << endl;
	cout << "95%" << endl;
	cout << "99%" << endl;
	cout << "Confidence Level (integer values only): ";
	cin.clear();
	cin.ignore();
	cin >> confidenceLevel;
	return confidenceLevel;
}

// Prompts the user for the confidence level and checks for non-integer inputs
int confidenceSelector()
{
	int confidenceLevel = 0;
	double zScore = 0;
	cout << "Select a Confidence Level" << endl;
	cout << "90%" << endl;
	cout << "95%" << endl;
	cout << "99%" << endl;
	cout << "Confidence Level (integer values only): ";
	cin >> confidenceLevel;
	cout << endl;

	// Error checking for non-integer values
	while(!cin)
	{
		confidenceLevel = clvlErrorHandling();
		cout << endl;
	}
	return confidenceLevel;
}

// Assigns the sample zScore depending on the chosen confidence level
double zScoreGenerator(int confidenceLevel)
{
	double zScore = 0;
	if(confidenceLevel == 90)
	{
		zScore = 1.645;
	}
	else if(confidenceLevel == 95)
	{
		zScore = 1.96;
	}
	else if(confidenceLevel == 99)
	{
		zScore = 2.58;
	}
	else
	{
		zScore = -1;	// Error condition for clvlErrorHandling()
	}
	return zScore;
}

// Calculates and outputs the sample mean, sample variance, error margin, and confidence interval.
void calcResults(vector<double> sample, int size, int clvl, double sum, double mean, double var, double dev, double zS)
{
	double stanError = 0;
	double errorMargin = 0;

	// Determines the Sample Mean and the Sample Variance
	sum = accumulate(sample.begin(), sample.end(), 0.0);
	mean = sum/(double)size;
	var  = (dev*dev)/(double)size;
	
	// Determines the Error Margin
	stanError = dev/sqrt((double)size);
	errorMargin = zS * stanError;

	// Output results
	cout << "Sample Mean: " << mean << endl;
	cout << "Sample Variance: " << var << endl;
	cout << "Error Margin: " << errorMargin << endl;
	cout << "Confidence Interval [" << clvl << "%]: (" << mean - errorMargin << ", " << mean + errorMargin << ")" << endl;
}


int main()
{
	// Variable Declarations
	vector<double> sampleVector;
	int sampleSize		= 0;
	int stanDev			= 0;
	int confidenceLevel = 0;
	double sampleSum 	= 0;
	double sampleMean 	= 0;
	double sampleVar  	= 0;
	double zScore 		= 0;
	double stanError 	= 0;
	double errorMargin	= 0;
	bool newRun = true;
	string input;
	
	sampleSize = sampleSizeGenerator();
	sampleVector.resize(sampleSize);
	addSampleData(sampleVector, sampleSize);
	stanDev = stanDevGenerator();
	while(newRun == true)
	{
		confidenceLevel = confidenceSelector();
		zScore = zScoreGenerator(confidenceLevel);
		while(zScore == -1)	// Error handling for invalid confidence levels
		{
			confidenceLevel = clvlErrorHandling();
			zScore = zScoreGenerator(confidenceLevel);
			cout << endl;
		}
		calcResults(sampleVector, sampleSize, confidenceLevel, sampleSum, sampleMean, sampleVar, stanDev, zScore);

		// Prompts the user for a new confidence level. Otherwise, prepare program for termination.
		cout << endl;
		cout << "Select a new confidence level for sample data?" << endl;
		cout << "Y/N: ";
		cin.ignore();	// Prevents the program from continuing without user input
		getline(cin, input);
		cout << endl;
		if(input=="Y"||input=="y")
		{
			newRun = true;
		}
		else if(input=="N"||input=="n")
		{
			newRun = false;
			break;
		}
		else
		{
			cout << "Invalid input: terminating program." << endl;
			newRun = false;
			break;
		}
	}
	return EXIT_SUCCESS;
}

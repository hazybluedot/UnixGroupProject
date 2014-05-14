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
	int confidenceLevel = 0;
	double sampleSum 	= 0;
	double sampleMean 	= 0;
	double sampleVar  	= 0;
	double stanDev	  	= 0;
	double zScore 		= 0;
	double stanError 	= 0;
	double errorMargin	= 0;
	bool newRun = true;
	string input = "";
	
	// Prompts the user for the sample size
	cout << "Enter Sample Size: ";
	cin >> sampleSize;
	while(!cin)			// Error handling for non-integer inputs
	{
		cout << endl << "Invalid Input." << endl << "Enter Sample Size (integer values only): ";
		cin.clear();
		cin.ignore();
		cin >> sampleSize;
	}
	sampleVector.resize(sampleSize);

	// Prompts the user for sample entries
	for(int n = 0; n < sampleSize; n++)
	{
		cout << "Enter Data for Sample " << n+1 << ": ";
		cin >> sampleVector[n];
		while(!cin)		// Error handling for non-numeric inputs
		{
			cout << endl << "Invalid Input. Enter Data for Sample " << n+1 << ": ";
			cin.clear();
			cin.ignore();
			cin >> sampleVector[n];
		}
	}
	
	// Prompts the user for standard deviation (if applicable)
	cout << "Enter Standard Deviation: ";
	cin >> stanDev;
	while(!cin)		// Error handling for non-numeric inputs
	{
		cout << endl << "Invalid Input. Enter Standard Deviation: ";
		cin.clear();
		cin.ignore();
		cin >> stanDev;
	}
	cout << endl;

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

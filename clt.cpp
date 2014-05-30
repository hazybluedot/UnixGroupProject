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
#include <vector>
#include <numeric>
#include <cmath>
#include <cctype> 
#include <string>
#include <cstdlib>
#include <sysexits.h>
#include <unistd.h>

#include "parameters.h"
#include "sample.hpp"

using namespace std;

void usage(ostream &os, int status) {
    os << "Usage: clt [-m MU] [-s SIGMA]" << endl;
    exit(status);
}

double require_strtod(const char* str) {
    double val;
    char *endptr;
    
    errno = 0;
    val = strtod(str, &endptr);
    if ((errno = ERANGE && ( val == HUGE_VAL || val == 0 )) 
            || (errno != 0 && val == 0)) {
        perror("strtod");
        exit(EX_DATAERR);
    }
    return val;
}

Parameters parse_options(int argc, char *argv[]) {
    int opt;
    double mu, sigma;
    
    mu = 0;
    sigma = 1;

    while ((opt = getopt(argc, argv, "m:s:12")) != -1) {
        switch(opt) {
        case 'm': /* population mean */
            mu = require_strtod(optarg);
            break;
        case 's': /* population variance */
            sigma = require_strtod(optarg);
            if (sigma <= 0) {
                cerr << optarg << ": population standard deviation must be non-zero and positive" << endl;
                usage(cerr, EX_USAGE);
            }
            break;
        case '1': /* one tail */
            break;
        case '2': /* two tail */
            break;
        default:
            usage(cerr, EX_USAGE);
        }
    }
    if ( std::isnan(mu) || std::isnan(sigma) ) {
        cerr << "current implementation requires known population parameters" << endl;
        usage(cerr, EX_USAGE);
    }

    return Parameters(mu, sigma);
}

int main(int argc, char* argv[])
{
	// Variable Declarations
	vector<double> sample;
        double stderr, z_score;

        Parameters pop = parse_options(argc, argv);

        sample = readSample(cin);

        stderr = pop.std_dev() / sqrt(sample.size());
        
        z_score = ( stat::mean(sample.begin(), sample.end()) - pop.mean() ) / stderr;

        cerr << "\u03BC: " << stat::mean(sample.begin(), sample.end()) << endl;
        cerr << "z-score: " << z_score << endl;

        if (z_score < 0)
            cout << 0.5* (1 + erf(z_score * M_SQRT1_2))  << endl;
        else
            cout << 0.5* (erfc(z_score * M_SQRT1_2))  << endl;

	return EXIT_SUCCESS;
}

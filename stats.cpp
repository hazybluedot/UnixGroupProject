#include <iostream>
#include <algorithm>
#include <vector>

#include "sample.hpp"

using std::cin;
using std::cout;
using std::vector;
using std::endl;

int main(int argc, char* argv[]) {
    std::vector<double> sample;
    double mean, var;
    int bias=1;

    sample = readSample(std::cin);

    mean = accumulate(sample.begin(), sample.end(), 0.0) / sample.size();
    
    vector<double> res(sample.size());
    transform(sample.begin(), sample.end(), res.begin(), [mean](double d) { return (d-mean)*(d-mean); } );
    
    var = accumulate(res.begin(), res.end(), 0.0) / (sample.size()-bias);

    cout << mean << ", " << var << endl;

    return EXIT_SUCCESS;
}

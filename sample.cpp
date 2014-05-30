#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>

std::vector<double> readSample(std::istream& is) {
    std::vector<double> samples;
    std::string line;

    while (getline(is, line)) {
        double s;

        errno = 0;
        s = strtod(line.c_str(), NULL);
        if ((errno = ERANGE && ( s == HUGE_VAL || s == 0 )) 
            || (errno != 0 && s == 0)) {
            perror("strtod");
            //exit(EX_DATAERR);
        }
        samples.push_back(s);
    }
    return samples;
}

#ifndef _SAMPLE_HPP_
#define _SAMPLE_HPP_

#include <vector>
#include <algorithm>

std::vector<double> readSample(std::istream& is);

namespace stat {
    template<typename InputIterator>
    double mean(InputIterator first, InputIterator last) {
        return std::accumulate(first, last, 0.0) / distance(first, last);
    }

    template<typename InputIterator>
    double stddev(InputIterator first, InputIterator last, double mu, int bias=1) {
        std::vector<double> res(std::distance(first, last));
        
        std::transform(first, last, [mu](double d) { return (d-mu)*(d-mu); });

        return std::accumulate(res.begin(), res.end(), 0.0) / (distance(first, last) - bias);
    }
}

#endif

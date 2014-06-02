#ifndef _STAT_HPP_
#define _STAT_HPP_

#include <numeric>
#include <vector>
#include <algorithm>

namespace stat {
    template<typename InputIterator>
    double mean(InputIterator first, InputIterator last) {
        return std::accumulate(first, last, 0.0) / distance(first, last);
    }

    template<typename InputIterator>
    double variance(InputIterator first, InputIterator last, double mu, int bias=1) {
        std::vector<double> res(std::distance(first, last));
        
        std::transform(first, last, res.begin(), [mu](double d) { return (d-mu)*(d-mu); });

        return std::accumulate(res.begin(), res.end(), 0.0) / (distance(first, last) - bias);
    }
}

#endif

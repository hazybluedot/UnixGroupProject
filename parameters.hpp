#ifndef _PARAMETERS_HPP_
#define _PARAMETERS_HPP_

class Parameters {

public:
    Parameters(double mu, double std_dev) : m_mean(mu), m_std_dev(std_dev) {};
    
    double mean() const { return m_mean; };
    double std_dev() const { return m_std_dev; };
    double var() const { return m_std_dev*m_std_dev; };
    
private:
    double m_mean;
    double m_std_dev;
};

#endif

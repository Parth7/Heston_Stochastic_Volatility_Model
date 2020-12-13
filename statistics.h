//
// Created by Parth Parakh on 12/12/20.
//

#ifndef HESTON_STOCHASTIC_VOLATILITY_MODEL_STATISTICS_H
#define HESTON_STOCHASTIC_VOLATILITY_MODEL_STATISTICS_H

#include<cmath>
#include<vector>

using namespace std;

class StatisticalDistribution
{
public:
    StatisticalDistribution();
    virtual ~StatisticalDistribution();

    virtual double pdf(const double& x)const =0;

    virtual double cdf(const double& x)const =0;

    virtual double inv_cdf(const double& quantile)const =0;

    virtual double mean()const =0;
    virtual double stdev()const =0;
    virtual double var()const =0;

    virtual void random_draws(const vector<double> &uniform_draws,  vector<double> &dist_draws)=0;
};

class StandardNormalDistribution: public StatisticalDistribution
{
public:
    StandardNormalDistribution();
    virtual ~StandardNormalDistribution();

    virtual double pdf(const double& x)const;
    virtual double cdf(const double& x)const;

    virtual double inv_cdf(const double& quantile)const;

    virtual double mean()const;
    virtual double stdev()const;
    virtual double var()const;

    virtual void random_draws(const vector<double> &uniform_draws, vector<double> &dist_draws);
};


#endif //HESTON_STOCHASTIC_VOLATILITY_MODEL_STATISTICS_H

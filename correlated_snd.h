//
// Created by Parth Parakh on 12/12/20.
//

#ifndef HESTON_STOCHASTIC_VOLATILITY_MODEL_CORRELATED_SND_H
#define HESTON_STOCHASTIC_VOLATILITY_MODEL_CORRELATED_SND_H

#include "statistics.h"

using namespace std;

class CorrelatedSND : public StandardNormalDistribution
{
protected:
    double rho;
    const vector<double>* uncorr_draws;

    // Modify an uncorrelated set of distribution draws to be correlated
    virtual void correlation_calc(vector<double>& dist_draws);

public:
    CorrelatedSND(const double _rho,const vector<double>* _uncorr_draws);
    virtual ~CorrelatedSND();

    // Obtain a sequence of correlated random draws from another set of SND draws
    virtual void random_draws(const vector<double>& uniform_draws,vector<double>& dist_draws);
};
#endif //HESTON_STOCHASTIC_VOLATILITY_MODEL_CORRELATED_SND_H

//
// Created by Parth Parakh on 12/12/20.
//

#ifndef __CORRELATED_SND_CPP
#define __CORRELATED_SND_CPP

#include "correlated_snd.h"
#include <iostream>
#include <cmath>

using namespace std;

CorrelatedSND::CorrelatedSND(const double _rho,const std::vector<double>* _uncorr_draws)
    : rho(_rho), uncorr_draws(_uncorr_draws) {}

CorrelatedSND::~CorrelatedSND() {}

// This carries out the actual correlation modification. It is easy to see that if
// rho = 0.0, then dist_draws is unmodified, whereas if rho = 1.0, then dist_draws
// is simply set equal to uncorr_draws. Thus with 0 < rho < 1 we have a
// weighted average of each set.
void CorrelatedSND::correlation_calc(std::vector<double>& dist_draws)
{
    for (int i=0; i<dist_draws.size(); i++)
    {
        dist_draws[i] = rho * (*uncorr_draws)[i] + dist_draws[i] * sqrt(1-rho*rho);
    }
}

void CorrelatedSND::random_draws(const vector<double>& uniform_draws,vector<double>& dist_draws)
{
    // The following functionality is lifted directly from statistics.h
    if (uniform_draws.size() != dist_draws.size())
    {
        cout << "Draws vectors are of unequal size in standard normal dist." << endl;
        return;
    }

    if (uniform_draws.size() % 2 != 0)
    {
        cout << "Uniform draw vector size not an even number." << endl;
        return;
    }

    for (int i=0; i<uniform_draws.size() / 2; i++)
    {
        dist_draws[2*i] = sqrt(-2.0*log(uniform_draws[2*i])) * sin(2*M_PI*uniform_draws[2*i+1]);
        dist_draws[2*i+1] = sqrt(-2.0*log(uniform_draws[2*i])) * cos(2*M_PI*uniform_draws[2*i+1]);
    }

    // Modify the random draws via the correlation calculation
    correlation_calc(dist_draws);

    return;
}

#endif


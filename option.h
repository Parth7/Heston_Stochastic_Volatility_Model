//
// Created by Parth Parakh on 12/12/20.
//

#ifndef HESTON_STOCHASTIC_VOLATILITY_MODEL_OPTION_H
#define HESTON_STOCHASTIC_VOLATILITY_MODEL_OPTION_H

#include"payoff.h"

class Option
{
public:
    PayOff *payoff;
    double K;
    double r;
    double T;

    Option(double &K_, double &r_, double &T_, PayOff* &payoff_);
    virtual ~Option();
};

#endif //HESTON_STOCHASTIC_VOLATILITY_MODEL_OPTION_H

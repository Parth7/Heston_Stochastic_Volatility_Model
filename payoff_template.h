//
// Created by Parth Parakh on 27/01/21.
//

#ifndef HESTON_STOCHASTIC_VOLATILITY_MODEL_PAYOFF_TEMPLATE_H
#define HESTON_STOCHASTIC_VOLATILITY_MODEL_PAYOFF_TEMPLATE_H

#include <algorithm>

enum class payoff_types
{
    call,
    put
};

class Payoff
{
    double strike;
public:
    Payoff(double K_):strike(K_){};
    template<payoff_types pt>
    double getpayoff(double spot);
};

template<>
double Payoff::getpayoff<payoff_types::call>(double spot)
{
    return std::max(spot-Payoff::strike,0.0);
}

template<>
double Payoff::getpayoff<payoff_types::put>(double spot)
{
    return std::max(0.0,Payoff::strike-spot);
}


#endif //HESTON_STOCHASTIC_VOLATILITY_MODEL_PAYOFF_TEMPLATE_H

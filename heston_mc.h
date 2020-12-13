//
// Created by Parth Parakh on 12/12/20.
//

#ifndef HESTON_STOCHASTIC_VOLATILITY_MODEL_HESTON_MC_H
#define HESTON_STOCHASTIC_VOLATILITY_MODEL_HESTON_MC_H

#include <cmath>
#include <vector>
#include "option.h"

using namespace std;
// The HestonEuler class stores the necessary information
// for creating the volatility and spot paths based on the
// Heston Stochastic Volatility model.
class HestonEuler
{
private:
    Option* pOption;
    double kappa;
    double theta;
    double xi;
    double rho;

public:
    HestonEuler(Option* _pOption,double _kappa, double _theta,double _xi, double _rho);
    virtual ~HestonEuler();

    // Calculate the volatility path
    void calc_vol_path(const vector<double>& vol_draws,vector<double>& vol_path);

    // Calculate the asset price path
    void calc_spot_path(const vector<double>& spot_draws,const vector<double>& vol_path,vector<double>& spot_path);
};
#endif //HESTON_STOCHASTIC_VOLATILITY_MODEL_HESTON_MC_H

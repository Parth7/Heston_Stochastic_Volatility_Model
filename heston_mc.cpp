//
// Created by Parth Parakh on 12/12/20.
//
#ifndef __HESTON_MC_CPP
#define __HESTON_MC_CPP

#include "heston_mc.h"
using namespace std;

HestonEuler::HestonEuler(Option* _pOption, double _kappa, double _theta,double _xi, double _rho) :
    pOption(_pOption), kappa(_kappa), theta(_theta), xi(_xi), rho(_rho) {}

HestonEuler::~HestonEuler() {}

void HestonEuler::calc_vol_path(const vector<double>& vol_draws,vector<double>& vol_path)
{
    size_t vec_size = vol_draws.size();
    double dt = pOption->T/static_cast<double>(vec_size);

    for (int i=1; i<vec_size; i++)
    {
        double v_max = max(vol_path[i-1],0.0);
        vol_path[i] = vol_path[i-1] + kappa*dt*(theta-v_max) + xi*sqrt(v_max*dt)*vol_draws[i-1];
    }
}

void HestonEuler::calc_spot_path(const vector<double>& spot_draws, const vector<double>& vol_path,vector<double>& spot_path)
{
    size_t vec_size = spot_draws.size();
    double dt = pOption->T/static_cast<double>(vec_size);

    for (int i=1; i<vec_size; i++)
    {
        double v_max = max(vol_path[i-1], 0.0);
        spot_path[i] = spot_path[i-1]*exp((pOption->r-0.5*v_max)*dt + sqrt(v_max*dt)*spot_draws[i-1]);
    }
}

#endif


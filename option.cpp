//
// Created by Parth Parakh on 12/12/20.
//

#include"option.h"

Option::Option(double &K_, double &r_, double &T_, PayOff *&payoff_):
    K(K_),r(r_),T(T_),payoff(payoff_)
{}

Option::~Option() {}


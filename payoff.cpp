//
// Created by Parth Parakh on 12/12/20.
//
#include "payoff.h"
#include<cmath>
#include <algorithm>

using namespace std;

PayOff::PayOff() {}
PayOff::~PayOff() noexcept {}

PayOffCall::PayOffCall(const double &K_): K(K_){}
PayOffCall::~PayOffCall() noexcept {}
double PayOffCall::operator()(const double &S) const
{
    return max(S-K,0.0);
}

PayOffPut::PayOffPut(const double &K_): K(K_){}
PayOffPut::~PayOffPut() noexcept {}
double PayOffPut::operator()(const double &S) const
{
    return max(K-S,0.0);
}

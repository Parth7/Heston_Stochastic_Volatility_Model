#include <iostream>

#include "payoff.h"
#include "option.h"
#include "correlated_snd.h"
#include "heston_mc.h"
#include"payoff_template.h"

using namespace std;

void generate_normal_correlation_paths(double rho,vector<double>& spot_normals,vector<double>& cor_normals)
{
    unsigned vals = spot_normals.size();

    StandardNormalDistribution snd;
    std::vector<double> snd_uniform_draws(vals,0.0);

    for(int i=0; i<snd_uniform_draws.size(); i++)
    {
        snd_uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
    }

    snd.random_draws(snd_uniform_draws, spot_normals);

    CorrelatedSND csnd(rho, &spot_normals);
    std::vector<double> csnd_uniform_draws(vals,0.0);

    for(int i=0; i<csnd_uniform_draws.size(); i++)
    {
        csnd_uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
    }

    csnd.random_draws(csnd_uniform_draws, cor_normals);
}

int main()
{
    unsigned num_sims = 100000;   // Number of simulated asset paths
    unsigned num_intervals = 1000;  // Number of intervals for the asset path to be sampled

    double S_0 = 100.0;    // Initial spot price
    double K = 100.0;      // Strike price
    double r = 0.0319;     // Risk-free rate
    double v_0 = 0.010201; // Initial volatility
    double T = 1.00;       // One year until expiry

    double rho = -0.7;     // Correlation of asset and volatility
    double kappa = 6.21;   // Mean-reversion rate
    double theta = 0.019;  // Long run average volatility
    double xi = 0.61;      // "Vol of vol"

    Payoff *py = new Payoff(K);
    PayOff* pPayOffCall = new PayOffCall(K);
    Option* pOption = new Option(K,r,T,pPayOffCall);
    HestonEuler hest_euler(pOption, kappa, theta, xi, rho);


    vector<double> spot_draws(num_intervals, 0.0);  // Vector of initial spot normal draws
    vector<double> vol_draws(num_intervals, 0.0);   // Vector of initial correlated vol normal draws
    vector<double> spot_prices(num_intervals, S_0);  // Vector of initial spot prices
    vector<double> vol_prices(num_intervals, v_0);   // Vector of initial vol prices

    // Monte Carlo options pricing
    double payoff_sum = 0.0;
    for (unsigned i=0; i<num_sims; i++)
    {
        //std::cout << "Calculating path " << i+1 << " of " << num_sims <<endl;
        generate_normal_correlation_paths(rho,spot_draws,vol_draws);
        hest_euler.calc_vol_path(vol_draws,vol_prices);
        hest_euler.calc_spot_path(spot_draws,vol_prices,spot_prices);
        //payoff_sum += pOption->payoff->operator()(spot_prices[num_intervals-1]);
        payoff_sum += py->getpayoff<payoff_types::call>(spot_prices[num_intervals-1]);
    }
    double option_price = (payoff_sum/static_cast<double>(num_sims))*exp(-r*T);
    cout<<"Option Price: "<< option_price<<endl;
    // Free memory
    delete pOption;
    delete pPayOffCall;
    return 0;
}

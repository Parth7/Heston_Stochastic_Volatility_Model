cmake_minimum_required(VERSION 3.17)
project(Heston_Stochastic_Volatility_Model)

set(CMAKE_CXX_STANDARD 14)

add_executable(Heston_Stochastic_Volatility_Model main.cpp payoff.h payoff.cpp option.h option.cpp statistics.h statistics.cpp correlated_snd.h correlated_snd.cpp heston_mc.h heston_mc.cpp payoff_template.h)
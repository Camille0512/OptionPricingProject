/**
* Author: Zhixin Li
* File name: FDMStrategy.cpp
* Date: 2023.04.28
* Description: The header file for the base FDM strategies.
* Version: 1.0
* */

#ifndef FDMSTRATEGY_CPP
#define FDMSTRATEGY_CPP

#include "FDMStrategy.hpp"

FDMStrategy::FDMStrategy() : sde(make_shared<GBM>()), n_step(1), dt(0), sqrt_dt(0) {}

FDMStrategy::FDMStrategy(shared_ptr<ISDE>& stochastic_eq, const int& step) :
	sde(stochastic_eq), n_step(step)
{
	dt = sde->getExpiry() / n_step;
	sqrt_dt = sqrt(dt);
}

FDMStrategy::~FDMStrategy() {}

double FDMStrategy::compute(const double& Si, const double& ti, const double& winer_increment, const double& winer_increment2)
{
	return 0;
}

const int FDMStrategy::getSteps() const
{ // Get the number of steps of the simulation
	return n_step;
}

const double FDMStrategy::getDeltaT() const
{ // Get the width of each step
	return sqrt_dt;
}

#endif
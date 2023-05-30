/**
* Author: Zhixin Li
* File name: FDMStrategy.hpp
* Date: 2023.04.28
* Description: The header file for the base FDM strategies.
* Version: 1.0
* */

#ifndef FDMSTRATEGY_HPP
#define FDMSTRATEGY_HPP

#include <memory>
#include "ISDE.hpp"
#include "GBM.hpp"
#include "OptionInfo.hpp"

using std::shared_ptr;

// TODO: Maybe can make it a Singleton
class FDMStrategy
{
protected:
	shared_ptr<ISDE> sde; // 0: GBM; 1: CEV; 2: CIR
	int n_step; // The step amount
	double dt; // The width for each step
	double sqrt_dt; // The square root of the Winner Process

public:
	FDMStrategy();
	FDMStrategy(shared_ptr<ISDE>& stochastic_eq, const int& step);
	virtual ~FDMStrategy();

	virtual double compute(const double& Si, const double& ti, const double& winer_increment, const double& winer_increment2); // Fill in the mesh array
	virtual const int getSteps() const final; // Get the number of steps of the simulation
	virtual const double getDeltaT() const final; // Get the width of each step
};

#endif
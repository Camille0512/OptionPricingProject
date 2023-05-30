/**
* Author: Zhixin Li
* File name: CIR.cpp
* Date: 2023.05.06
* Description: The implementation file for the CIR SDE. CIR model mainly used in interest rate product pricing.
* Version: 1.0
* */

#ifndef CIR_CPP
#define CIR_CPP

#include <iostream>
#include "CIR.hpp"

using std::cout;
using std::endl;

CIR::CIR() : mean_reversion_rate(1), instant_rate(0.02) {}

CIR::CIR(shared_ptr<OptionInfo>& opt, const double& rev_r, const double& inst_r, const double& init_condition) :
	ISDE(opt, init_condition), mean_reversion_rate(rev_r), instant_rate(inst_r)
{
	if (rev_r * inst_r * 2 < pow(opt->getVolatility(), 2))
	{
		cout << "[Warning] The result computed by the CIR SDE may not hold. Please reset the parameters and make sure 2ab >= c^2 holds." << endl;
	}
}

CIR::~CIR() {}

double CIR::Drift(const double& S, const double& t)
{
	return mean_reversion_rate * (option->getIR() -instant_rate);
}

double CIR::Diffusion(const double& S, const double& t)
{
	return option->getVolatility() * sqrt(instant_rate);
}

double CIR::DiffusionDerivative(const double& S, const double& t)
{
	return  option->getVolatility();
}

double CIR::DriftCorrected(const double& S, const double& t, const double& B)
{
	return Drift(S, t) - B * Diffusion(S, t) * DiffusionDerivative(S, t);
}

void CIR::resetMeanReversionRate(const double& val)
{
	mean_reversion_rate = val;
}

void CIR::resetInstantRate(const double& val)
{
	instant_rate = val;
}

#endif
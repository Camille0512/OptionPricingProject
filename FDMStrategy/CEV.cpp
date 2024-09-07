/**
* Author: Zhixin Li
* File name: CEV.cpp
* Date: 2023.05.06
* Description: The implementation file for the CEV SDE.
* Version: 1.0
* */

#ifndef CEV_CPP
#define CEV_CPP

#include "CEV.hpp"

CEV::CEV() : beta(0) {}

CEV::CEV(shared_ptr<OptionInfo>& opt, const double& beta_val, const double& init_condition) : 
	ISDE(opt, init_condition), beta(beta_val) {}

CEV::~CEV() {}

double CEV::Drift(const double& S, const double& t)
{
	return (option->getIR() - option->getDividend()) * S;
}

double CEV::Diffusion(const double& S, const double& t)
{
	return option->getVolatility() * pow(S, beta);
}

double CEV::DiffusionDerivative(const double& S, const double& t)
{
	if (beta > 1.0)
	{
		return option->getVolatility() * beta * pow(S, beta - 1.0);
	}
	else
	{
		return  option->getVolatility() * beta * pow(S, 1.0 - beta);
	}
}

double CEV::DriftCorrected(const double& S, const double& t, const double& B)
{
	return Drift(S, t) - B * Diffusion(S, t) * DiffusionDerivative(S, t);
}

#endif
/**
* Author: Zhixin Li
* File name: GBM.cpp
* Date: 2023.04.28
* Description: The implementation file for the GBM SDE.
* Version: 1.0
* */

#ifndef GBM_CPP
#define GBM_CPP

#include "GBM.hpp"

GBM::GBM() {}

GBM::GBM(shared_ptr<OptionInfo>& opt, const double& init_condition) : ISDE(opt, init_condition) {}

GBM::~GBM() {}

double GBM::Drift(const double& S, const double& t)
{
	return (option->getIR() - option->getDividend()) * S;
}

double GBM::Diffusion(const double& S, const double& t)
{
	return option->getVolatility() * S;
}

double GBM::DiffusionDerivative(const double& S, const double& t)
{
	return option->getVolatility();
}

double GBM::DriftCorrected(const double& S, const double& t, const double& B)
{
	return Drift(S, t) - B * Diffusion(S, t) * DiffusionDerivative(S, t);
}

#endif
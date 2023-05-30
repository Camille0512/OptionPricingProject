/**
* Author: Zhixin Li
* File name: HeunFDM.cpp
* Date: 2023.04.28
* Description: The header file for the Heun FDM strategies.
* Version: 1.0
* */

#ifndef HEUNFDM_CPP
#define HEUNFDM_CPP

#include "HeunFDM.hpp"
#include <iostream>

HeunFDM::HeunFDM() : FDMStrategy() {}

HeunFDM::HeunFDM(shared_ptr<ISDE>& stochastic_eq, const int& step) : FDMStrategy(stochastic_eq, step) {}

HeunFDM::~HeunFDM() {}

double HeunFDM::compute(const double& Si, const double& ti, const double& winer_increment, const double& winer_increment2)
{
	double a = sde->Drift(Si, ti);
	double b = sde->Diffusion(Si, ti);
	double sup_val = Si + a * dt + b * sqrt_dt * winer_increment;
	return Si + 0.5 * (sde->Drift(sup_val, ti) + a) * dt + 0.5 * (sde->Diffusion(sup_val, ti) + b) * sqrt_dt * winer_increment;
}

#endif
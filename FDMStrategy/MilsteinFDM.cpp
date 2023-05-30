/**
* Author: Zhixin Li
* File name: MilsteinFDM.cpp
* Date: 2023.04.28
* Description: The header file for the Milstein FDM strategies.
* Version: 1.0
* */

#ifndef MILSTEINFDM_CPP
#define MILSTEINFDM_CPP

#include "MilsteinFDM.hpp"
#include <iostream>

MilsteinFDM::MilsteinFDM() : FDMStrategy() {}

MilsteinFDM::MilsteinFDM(shared_ptr<ISDE>& stochastic_eq, const int& step) : FDMStrategy(stochastic_eq, step) {}

MilsteinFDM::~MilsteinFDM() {}

double MilsteinFDM::compute(const double& Si, const double& ti, const double& winer_increment, const double& winer_increment2)
{
	return Si + sde->Drift(Si, ti) * dt + sde->Diffusion(Si, ti) * sqrt_dt * winer_increment
		+ 0.5 * dt * sde->Diffusion(Si, ti) * sde->DiffusionDerivative(Si, ti) * (pow(winer_increment, 2) - 1.0);
}

#endif
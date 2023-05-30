/**
* Author: Zhixin Li
* File name: EulerFDM.cpp
* Date: 2023.04.28
* Description: The header file for the Euler FDM strategies.
* Version: 1.0
* */

#ifndef EULERFDM_CPP
#define EULERFDM_CPP

#include "EulerFDM.hpp"
#include <iostream>

EulerFDM::EulerFDM() : FDMStrategy() {}

EulerFDM::EulerFDM(shared_ptr<ISDE>& stochastic_eq, const int& step) : FDMStrategy(stochastic_eq, step) {}

EulerFDM::~EulerFDM() {}

double EulerFDM::compute(const double& Si, const double& ti, const double& winer_increment, const double& winer_increment2)
{
	return Si + sde->Drift(Si, ti) * dt + sde->Diffusion(Si, ti) * sqrt_dt * winer_increment;
}

#endif
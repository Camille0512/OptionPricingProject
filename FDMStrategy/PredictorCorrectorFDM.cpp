/**
* Author: Zhixin Li
* File name: PredictorCorrectorFDM.cpp
* Date: 2023.04.28
* Description: The header file for the Predictor Corrector FDM strategies.
* Version: 1.0
* */

#ifndef PREDICTORCORRECTORFDM_CPP
#define PREDICTORCORRECTORFDM_CPP

#include "PredictorCorrectorFDM.hpp"
#include <iostream>

using std::cout;
using std::endl;

PredictorCorrectorFDM::PredictorCorrectorFDM() : FDMStrategy(), a(0), b(0) {}

PredictorCorrectorFDM::PredictorCorrectorFDM(shared_ptr<ISDE>& stochastic_eq, const int& step, const double& a_val, const double& b_val) :
	FDMStrategy(stochastic_eq, step), a(a_val), b(b_val) {}

PredictorCorrectorFDM::~PredictorCorrectorFDM() {}

double PredictorCorrectorFDM::compute(const double& Si, const double& ti, const double& winer_increment, const double& winer_increment2)
{
	double mid_val = Si + sde->Drift(Si, ti) * dt + sde->Diffusion(Si, ti) * sqrt_dt * winer_increment;
	double drift_term = (a * sde->Drift(mid_val, ti + dt) + ((1.0 - a) * sde->Drift(Si, ti))) * dt;
	double diffusion_term = (b * sde->Diffusion(mid_val, ti + dt) + ((1.0 - b) * sde->Diffusion(Si, ti))) * sqrt_dt * winer_increment;
	return Si + drift_term + diffusion_term;
}

#endif
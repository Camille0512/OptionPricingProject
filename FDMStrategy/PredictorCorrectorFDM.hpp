/**
* Author: Zhixin Li
* File name: PredictorCorrectorFDM.hpp
* Date: 2023.05.06
* Description: The header file for the Predictor Corrector FDM strategies.
* Version: 1.0
* */

#ifndef PREDICTORCORRECTORFDM_HPP
#define PREDICTORCORRECTORFDM_HPP

#include <memory>
#include "ISDE.hpp"
#include "GBM.hpp"
#include "OptionInfo.hpp"
#include "FDMStrategy.hpp"

using std::shared_ptr;

// TODO: Maybe can make it a Singleton
class PredictorCorrectorFDM : public FDMStrategy
{
private:
	double a;
	double b;

public:
	PredictorCorrectorFDM();
	PredictorCorrectorFDM(shared_ptr<ISDE>& stochastic_eq, const int& step, const double& a_val, const double& b_val);
	virtual ~PredictorCorrectorFDM();

	double compute(const double& Si, const double& ti, const double& winer_increment, const double& winer_increment2); // Fill in the mesh array
};

#endif
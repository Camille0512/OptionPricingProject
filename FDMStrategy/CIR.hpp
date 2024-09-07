/**
* Author: Zhixin Li
* File name: CIR.hpp
* Date: 2023.05.06
* Description: The header file for the CIR SDE. CIR model mainly used in interest rate product pricing.
* Version: 1.0
* */

#ifndef CIR_HPP
#define CIR_HPP

#include <memory>
#include "ISDE.hpp"
#include "OptionInfo.hpp"

using std::shared_ptr;

class CIR : public ISDE
{
private:
	double mean_reversion_rate;
	double instant_rate;

public:
	// Constructor & Destructor
	CIR();
	CIR(shared_ptr<OptionInfo>& opt, const double& rev_r, const double& inst_r, const double& init_condition = 0);
	virtual ~CIR();

	double Drift(const double& S, const double& t) override;
	double Diffusion(const double& S, const double& t) override;

	// GBM can be extended to the case where there are multiple correlated price paths
	double DiffusionDerivative(const double& S, const double& t) override;
	double DriftCorrected(const double& S, const double& t, const double& B) override;

	void resetMeanReversionRate(const double& val);
	void resetInstantRate(const double& val);
};

#endif
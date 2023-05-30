/**
* Author: Zhixin Li
* File name: CEV.hpp
* Date: 2023.05.06
* Description: The header file for the CEV SDE.
* Version: 1.0
* */

#ifndef CEV_HPP
#define CEV_HPP

#include <memory>
#include "ISDE.hpp"
#include "OptionInfo.hpp"

using std::shared_ptr;

class CEV : public ISDE
{
private:
	double beta;

public:
	// Constructor & Destructor
	CEV();
	CEV(shared_ptr<OptionInfo>& opt, const double& beta_val, const double& init_condition = 0);
	virtual ~CEV();

	double Drift(const double& S, const double& t) override;
	double Diffusion(const double& S, const double& t) override;

	// GBM can be extended to the case where there are multiple correlated price paths
	double DiffusionDerivative(const double& S, const double& t) override;
	double DriftCorrected(const double& S, const double& t, const double& B) override;
};

#endif
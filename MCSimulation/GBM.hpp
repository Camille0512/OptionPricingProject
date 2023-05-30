/**
* Author: Zhixin Li
* File name: GBM.hpp
* Date: 2023.04.28
* Description: The header file for the GBM SDE.
* Version: 1.0
* */

#ifndef GBM_HPP
#define GBM_HPP

#include <memory>
#include "ISDE.hpp"
#include "OptionInfo.hpp"

using std::shared_ptr;

class GBM : public ISDE
{
public:
	// Constructor & Destructor
	GBM();
	GBM(shared_ptr<OptionInfo>& opt, const double& init_condition = 0);
	virtual ~GBM();

	double Drift(const double& S, const double& t) override;
	double Diffusion(const double& S, const double& t) override;

	// GBM can be extended to the case where there are multiple correlated price paths
	double DiffusionDerivative(const double& S, const double& t) override;
	double DriftCorrected(const double& S, const double& t, const double& B) override;
};

#endif
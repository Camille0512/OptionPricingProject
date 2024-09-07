/**
* Author: Zhixin Li
* File name: ISDE.hpp
* Date: 2023.04.28
* Description: The header file for the abstract SDE.
* Version: 1.0
* */

#ifndef ISDE_HPP
#define ISDE_HPP

#include <memory>
#include "OptionInfo.hpp"

using std::shared_ptr;
using std::make_shared;

class ISDE
{
protected:
	shared_ptr<OptionInfo> option; // All the option information
	double expiry; // Expiry
	double init_cond; // Initial condition

public:
	ISDE();
	ISDE(shared_ptr<OptionInfo>& option, const double& init_condition = 0);
	virtual ~ISDE();

	virtual double Drift(const double& S, const double& t) = 0;
	virtual double Diffusion(const double& S, const double& t) = 0;

	virtual double DiffusionDerivative(const double& S, const double& t) = 0;
	virtual double DriftCorrected(const double& S, const double& t, const double& B) = 0;

	virtual double getInitialCondition() final; // To get the initial condition for the SDE
	virtual void setInitialCondition(const double& val) final; // To set the initial condition for the SDE
	virtual double getExpiry() final; // To get the expiry
	virtual void setExpiry(const double& val) final; // To set the expiry
};

#endif
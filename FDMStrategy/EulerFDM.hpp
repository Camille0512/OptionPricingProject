/**
* Author: Zhixin Li
* File name: EulerFDM.hpp
* Date: 2023.05.06
* Description: The header file for the Euler FDM strategies.
* Version: 1.0
* */

#ifndef EULERFDM_HPP
#define EULERFDM_HPP

#include <memory>
#include "ISDE.hpp"
#include "GBM.hpp"
#include "OptionInfo.hpp"
#include "FDMStrategy.hpp"

using std::shared_ptr;

// TODO: Maybe can make it a Singleton
class EulerFDM : public FDMStrategy
{
public:
	EulerFDM();
	EulerFDM(shared_ptr<ISDE>& stochastic_eq, const int& step);
	virtual ~EulerFDM();

	double compute(const double& Si, const double& ti, const double& winer_increment, const double& winer_increment2); // Fill in the mesh array
};

#endif
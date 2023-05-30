/**
* Author: Zhixin Li
* File name: MilsteinFDM.hpp
* Date: 2023.05.06
* Description: The header file for the Milstein FDM strategies.
* Version: 1.0
* */

#ifndef MILSTEINFDM_HPP
#define MILSTEINFDM_HPP

#include <memory>
#include "ISDE.hpp"
#include "GBM.hpp"
#include "OptionInfo.hpp"
#include "FDMStrategy.hpp"

using std::shared_ptr;

// TODO: Maybe can make it a Singleton
class MilsteinFDM : public FDMStrategy
{
public:
	MilsteinFDM();
	MilsteinFDM(shared_ptr<ISDE>& stochastic_eq, const int& step);
	virtual ~MilsteinFDM();

	double compute(const double& Si, const double& ti, const double& winer_increment, const double& winer_increment2); // Fill in the mesh array
};

#endif
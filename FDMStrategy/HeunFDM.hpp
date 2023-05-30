/**
* Author: Zhixin Li
* File name: HeunFDM.hpp
* Date: 2023.05.06
* Description: The header file for the Heun FDM strategies.
* Version: 1.0
* */

#ifndef HEUNFDM_HPP
#define HEUNFDM_HPP

#include <memory>
#include "ISDE.hpp"
#include "GBM.hpp"
#include "OptionInfo.hpp"
#include "FDMStrategy.hpp"

using std::shared_ptr;

// TODO: Maybe can make it a Singleton
class HeunFDM : public FDMStrategy
{
public:
	HeunFDM();
	HeunFDM(shared_ptr<ISDE>& stochastic_eq, const int& step);
	virtual ~HeunFDM();

	double compute(const double& Si, const double& ti, const double& winer_increment, const double& winer_increment2); // Fill in the mesh array
};

#endif
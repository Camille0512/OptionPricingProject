/**
* Author: Zhixin Li
* File name: ISDE.cpp
* Date: 2023.04.28
* Description: The header file for the abstract SDE.
* Version: 1.0
* */

#ifndef ISDE_CPP
#define ISDE_CPP

#include <iostream>
#include "ISDE.hpp"

using std::cout;
using std::endl;

ISDE::ISDE() : option(new OptionInfo()), expiry(0.0), init_cond(0.0) {}

ISDE::ISDE(shared_ptr<OptionInfo>& option, const double& init_condition) : option(option), init_cond(init_condition)
{
	expiry = option->getMaturity();
}

ISDE::~ISDE() {}

double ISDE::getInitialCondition()
{
	return init_cond;
}

void ISDE::setInitialCondition(const double& val)
{
	init_cond = val;
}

double ISDE::getExpiry()
{
	return expiry;
}

void ISDE::setExpiry(const double& val)
{
	expiry = val;
}

#endif
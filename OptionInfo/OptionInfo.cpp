/**
* Author: Zhixin Li
* File name: OptionInfo.cpp
* Date: 2023.04.29
* Description: The implementation file for the abstract Option information.
* Version: 1.0
* */

#ifndef OPTIONINFO_CPP
#define OPTIONINFO_CPP

#include <exception>
#include <iostream>
#include "OptionInfo.hpp"

OptionInfo::OptionInfo() : S0(100), X(100), T(1), r(0.02), sig(0.5), d(0.01), option_type(1)
{
	std::cout << "[Warning] The option information may not be what you expect." << std::endl;
}

OptionInfo::OptionInfo(const double & asset_price, const double& strike, const double& expiry, const double& ir, const double& volatility, const double& div, const int& type) :
	S0(asset_price), X(strike), T(expiry), r(ir), sig(volatility), d(div), option_type(type)
{
	if (type != 1 && type != -1) throw std::exception("Wrong input for the option type (1 : call, -1 : put).");
}

OptionInfo::~OptionInfo() {}

const double OptionInfo::getUnderlyingPrice() { return S0; }

const double OptionInfo::getStrike() { return X; }

const double OptionInfo::getMaturity() { return T; }

const double OptionInfo::getIR() { return r; }

const double OptionInfo::getVolatility() { return sig; }

const double OptionInfo::getDividend() { return d; }

const int OptionInfo::getOptionType() { return option_type; }

void OptionInfo::resetVolatility(const double& val) { sig = val; }

#endif
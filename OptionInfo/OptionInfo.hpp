/**
* Author: Zhixin Li
* File name: OptionInfo.hpp
* Date: 2023.04.29
* Description: The header file for the abstract Option information.
* Version: 1.0
* */

#ifndef OPTIONINFO_HPP
#define OPTIONINFO_HPP

class OptionInfo
{
private:
	double S0; // Current price of the underlying asset
	double X; // Strike
	double T; // Maturity, usually measured in year, should align with IR
	double r; // Interest rate, usually measured in year, should align with maturity
	double sig; // Volatility

	double d; // Dividend

	int option_type; // 1 - call; -1 - put

public:
	explicit OptionInfo();
	explicit OptionInfo(const double& asset_price, const double& strike, const double& expiry, const double& ir, const double& volatility, const double& div, const int& type);
	virtual ~OptionInfo();

	// Member function
	const double getUnderlyingPrice();
	const double getStrike();
	const double getMaturity();
	const double getIR();
	const double getVolatility();
	const double getDividend();
	const int getOptionType();

	void resetVolatility(const double& val);
};

#endif
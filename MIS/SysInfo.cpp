/**
* Author: Zhixin Li
* File name: SysInfo.cpp
* Date: 2023.05.01
* Description: The implementation file for the message delivery.
* Version: 1.0
* */

#ifndef SYSINFO_CPP
#define SYSINFO_CPP

#include <iostream>
#include "SysInfo.hpp"

using std::cout;
using std::endl;

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
SysInfo<T, Container, Alloc>::SysInfo(shared_ptr<OptionInfo>& option_ptr) :
	MIS<T, Container, Alloc>(option_ptr), option_theory_price(0), option_info_counter(0), option_price_counter(0) {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
SysInfo<T, Container, Alloc>::~SysInfo() {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
void SysInfo<T, Container, Alloc>::getOptionPrice(const double& price)
{ // Get the price gotten from MC simulation and assign to the data member
	option_theory_price = price;
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
const void SysInfo<T, Container, Alloc>::showCounter() const
{ // Show the observers number of each observers from different system
	cout << "The number of the option information observer is #" << option_info_counter << "." << endl;
	cout << "The number of the option price observer is #" << option_price_counter << "." << endl;
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
const void SysInfo<T, Container, Alloc>::printOptionInfo()
{
	option_info_counter++;
	cout << "[Option information]" << endl;
	cout << "  Underlying asset price: " << MIS<T, Container, Alloc>::option_info->getUnderlyingPrice() << "." << endl;
	cout << "  Strike:                 " << MIS<T, Container, Alloc>::option_info->getStrike() << "." << endl;
	cout << "  Maturity:               " << MIS<T, Container, Alloc>::option_info->getMaturity() << "." << endl;
	cout << "  Interest rate:          " << MIS<T, Container, Alloc>::option_info->getIR() << "." << endl;
	cout << "  Volatility:             " << MIS<T, Container, Alloc>::option_info->getVolatility() << "." << endl;
	cout << "  Dividend:               " << MIS<T, Container, Alloc>::option_info->getDividend() << "." << endl;
	cout << "  Option type:            " << MIS<T, Container, Alloc>::option_info->getOptionType() << "." << endl;
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
const void SysInfo<T, Container, Alloc>::printOptionPrice()
{
	option_price_counter++;
	cout << "[Option theory price] $" << option_theory_price << endl;
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
void SysInfo<T, Container, Alloc>::removeObserver()
{
	auto cate = MIS<T, Container, Alloc>::detach();
	if (cate == 0)
	{
		cout << "The option information observer is removed.." << endl;
	}
	else
	{
		cout << "The option price observer is removed.." << endl;
	}
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
shared_ptr<MIS<T, Container, Alloc>> SysInfo<T, Container, Alloc>::transType(shared_ptr<SysInfo<T, Container, Alloc>>& ptr)
{
	auto mis_ptr = std::static_pointer_cast<MIS<T, Container, Alloc>>(ptr);
	return mis_ptr;
}

#endif
/**
* Author: Zhixin Li
* File name: AsianPricer.cpp
* Date: 2023.05.06
* Description: The implementation file for the Asian Option pricer.
* Version: 1.0
* */

#ifndef ASIANPRICER_CPP
#define ASIANPRICER_CPP

#include <iostream>
#include <algorithm>
#include <numeric>
#include "AsianPricer.hpp"

using std::max;
using std::accumulate;

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
AsianPricer<T, Container, Alloc>::AsianPricer() : Pricer<T, Container, Alloc>() {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
AsianPricer<T, Container, Alloc>::AsianPricer(Container<T, Alloc>& prices, shared_ptr<OptionInfo>& option) :
	Pricer<T, Container, Alloc>(prices, option) {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
AsianPricer<T, Container, Alloc>::~AsianPricer() {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
double AsianPricer<T, Container, Alloc>::pricing()
{ // Option pricing
	double avg_price = accumulate(this->price_path.begin(), this->price_path.end(), 0.0) / this->price_path.size();
	int option_type = this->option_info->getOptionType();

	if (option_type == 1)
	{ // Call option
		return max(avg_price - this->option_info->getStrike(), 0.0) * this->DiscountFactor();
	}
	else
	{ // Put option
		return max(this->option_info->getStrike() - avg_price, 0.0) * this->DiscountFactor();
	}
}

#endif
/**
* Author: Zhixin Li
* File name: VanillaPricer.cpp
* Date: 2023.05.06
* Description: The implementation file for the vanilla Option pricer.
* Version: 1.0
* */

#ifndef VANILLAPRICER_CPP
#define VANILLAPRICER_CPP

#include <iostream>
#include <algorithm>
#include "VanillaPricer.hpp"

using std::max;

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
VanillaPricer<T, Container, Alloc>::VanillaPricer() : Pricer<T, Container, Alloc>() {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
VanillaPricer<T, Container, Alloc>::VanillaPricer(Container<T, Alloc>& prices, shared_ptr<OptionInfo>& option) : 
	Pricer<T, Container, Alloc>(prices, option) {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
VanillaPricer<T, Container, Alloc>::~VanillaPricer() {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
double VanillaPricer<T, Container, Alloc>::pricing()
{ // Option pricing
	using iter_type = Container<T, Alloc>::iterator;
	iter_type iter = this->price_path.end(); iter--; // To get the last element of the path
	int option_type = this->option_info->getOptionType();

	if (option_type == 1)
	{ // Call option
		return max(*iter - this->option_info->getStrike(), 0.0) * this->DiscountFactor();
	}
	else
	{ // Put option
		return max(this->option_info->getStrike() - *iter, 0.0) * this->DiscountFactor();
	}
}

#endif
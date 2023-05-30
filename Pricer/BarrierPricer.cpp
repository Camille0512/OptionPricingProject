/**
* Author: Zhixin Li
* File name: BarrierPricer.cpp
* Date: 2023.05.06
* Description: The implementation file for the Barrier Option pricer.
* Version: 1.0
* */

#ifndef BARRIERPRICER_CPP
#define BARRIERPRICER_CPP

#include <iostream>
#include <algorithm>
#include <numeric>
#include "BarrierPricer.hpp"

using std::max;
using std::max_element;
using std::min_element;
using std::accumulate;

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
BarrierPricer<T, Container, Alloc>::BarrierPricer() : Pricer<T, Container, Alloc>(), barrier_type(0), barrier(0) {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
BarrierPricer<T, Container, Alloc>::BarrierPricer(Container<T, Alloc>& prices, shared_ptr<OptionInfo>& option, const int& bar_type, const double& bar) :
	Pricer<T, Container, Alloc>(prices, option), barrier_type(bar_type), barrier(bar) {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
BarrierPricer<T, Container, Alloc>::~BarrierPricer() {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
double BarrierPricer<T, Container, Alloc>::pricing()
{ // Option pricing
	using iter_type = Container<T, Alloc>::iterator;
	iter_type iter = this->price_path.end(); iter--; // To get the last element of the path
	int option_type = this->option_info->getOptionType();

	if (barrier_type == 1)
	{ // Knock-in barrier option
		if (option_type == 1)
		{ // Call option
			iter_type max_price = max_element(this->price_path.begin(), this->price_path.end());
			
			if (*max_price < barrier) return 0; // The option is never entered into existence
			else return max(*iter - this->option_info->getStrike(), 0.0) * this->DiscountFactor();
		}
		else
		{ // Put option
			iter_type min_price = min_element(this->price_path.begin(), this->price_path.end());
			
			if (*min_price > barrier) return 0; // The option is never entered into existence
			else  return max(this->option_info->getStrike() - *iter, 0.0) * this->DiscountFactor();
		}
	}
	else
	{
		if (option_type == 1)
		{ // Call option
			iter_type max_price = max_element(this->price_path.begin(), this->price_path.end());

			if (*max_price < barrier) return max(*iter - this->option_info->getStrike(), 0.0) * this->DiscountFactor();
			else return 0; // The option is never entered into existence
		}
		else
		{ // Put option
			iter_type min_price = min_element(this->price_path.begin(), this->price_path.end());

			if (*min_price > barrier) return max(this->option_info->getStrike() - *iter, 0.0) * this->DiscountFactor();
			else return 0; // The option is never entered into existence
		}
	}
}

#endif
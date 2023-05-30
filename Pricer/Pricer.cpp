/**
* Author: Zhixin Li
* File name: Pricer.cpp
* Date: 2023.04.30
* Description: The implementation file for the abstract Option pricer.
* Version: 1.0
* */

#ifndef PRICER_CPP
#define PRICER_CPP

#include <iostream>
#include <algorithm>
#include "Pricer.hpp"

using std::max;

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
Pricer<T, Container, Alloc>::Pricer() : price_path(Container<T, Alloc>()), option_info(make_shared<OptionInfo>()) {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
Pricer<T, Container, Alloc>::Pricer(Container<T, Alloc>& prices, shared_ptr<OptionInfo>& option) : price_path(prices), option_info(option) {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
Pricer<T, Container, Alloc>::~Pricer() {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
double Pricer<T, Container, Alloc>::DiscountFactor()
{ // Discount the values from the future to the present
	return 1 / exp(option_info->getIR() * option_info->getMaturity());
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
double Pricer<T, Container, Alloc>::pricing()
{ // Option pricing
	return 0;
}

#endif
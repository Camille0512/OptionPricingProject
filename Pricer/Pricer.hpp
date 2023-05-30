/**
* Author: Zhixin Li
* File name: Pricer.hpp
* Date: 2023.04.30
* Description: The header file for the abstract Option pricer.
* Version: 1.0
* */

#ifndef PRICER_HPP
#define PRICER_HPP

#include <vector>
#include <memory>
#include <deque>
#include <functional>
#include "OptionInfo.hpp"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::deque;
using std::allocator;

template<typename T, template<typename T, typename Alloc> class Container = deque, typename Alloc = allocator<T>>
class Pricer
{
protected:
	Container<T, Alloc> price_path;
	shared_ptr<OptionInfo> option_info;

public:
	Pricer(); // Not going to use it, just delete
	explicit Pricer(Container<T, Alloc>& prices, shared_ptr<OptionInfo>& option);
	virtual ~Pricer();

	// Memeber functions
	virtual double DiscountFactor() final; // Discount the values from the future to the present
	virtual double pricing(); // Option pricing
};

#endif
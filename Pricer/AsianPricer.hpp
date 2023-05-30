/**
* Author: Zhixin Li
* File name: AsianPricer.hpp
* Date: 2023.05.06
* Description: The header file for the Asian Option pricer.
* Version: 1.0
* */

#ifndef ASIANPRICER_HPP
#define ASIANPRICER_HPP

#include <vector>
#include <memory>
#include <deque>
#include <functional>
#include "OptionInfo.hpp"
#include "Pricer.hpp"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::deque;
using std::allocator;

template<typename T, template<typename T, typename Alloc> class Container = deque, typename Alloc = allocator<T>>
class AsianPricer : public Pricer<T, Container, Alloc>
{
public:
	AsianPricer(); // Not going to use it, just delete
	explicit AsianPricer(Container<T, Alloc>& prices, shared_ptr<OptionInfo>& option);
	virtual ~AsianPricer();

	// Memeber functions
	double pricing(); // Option pricing
};

#endif
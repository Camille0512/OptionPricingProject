/**
* Author: Zhixin Li
* File name: BarrierPricer.hpp
* Date: 2023.05.06
* Description: The header file for the Barrier Option pricer.
* Version: 1.0
* */

#ifndef BARRIERPRICER_HPP
#define BARRIERPRICER_HPP

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
class BarrierPricer : public Pricer<T, Container, Alloc>
{
private:
	int barrier_type; // 1 : knock-in barrier option; other : knock-out barrier option
	double barrier; // The barrier price

public:
	BarrierPricer(); // Not going to use it, just delete
	explicit BarrierPricer(Container<T, Alloc>& prices, shared_ptr<OptionInfo>& option, const int& bar_type, const double& bar);
	virtual ~BarrierPricer();

	// Memeber functions
	double pricing(); // Option pricing
};

#endif
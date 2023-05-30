/**
* Author: Zhixin Li
* File name: VanillaPricer.hpp
* Date: 2023.05.06
* Description: The header file for the vanilla Option pricer.
* Version: 1.0
* */

#ifndef VANILLAPRICER_HPP
#define VANILLAPRICER_HPP

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
class VanillaPricer : public Pricer<T, Container, Alloc>
{
public:
	VanillaPricer(); // Not going to use it, just delete
	explicit VanillaPricer(Container<T, Alloc>& prices, shared_ptr<OptionInfo>& option);
	virtual ~VanillaPricer();

	// Memeber functions
	double pricing(); // Option pricing
};

#endif
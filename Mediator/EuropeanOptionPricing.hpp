/**
* Author: Zhixin Li
* File name: EuropeanOptionPricing.hpp
* Date: 2023.04.28
* Description: The header file for the mediator for the European options.
* Version: 1.0
* */

#ifndef EUROPEANOPTIONPRICING_HPP
#define EUROPEANOPTIONPRICING_HPP

#include "Mediator.hpp"
#include "VanillaPricer.hpp"

template<typename T, template<typename T, typename Alloc> class Container = deque, typename Alloc = allocator<T>>
class EuropeanOptionPricing : public Mediator<T, Container, Alloc>
{
public:
	EuropeanOptionPricing(const int& sims, const int& step, const double& init_condition);
	virtual ~EuropeanOptionPricing();

	// Member functions
	const void insertUserMonitor(Observers<T, Container, Alloc>& obs, const string& name, const int& cate);
	void removeUser(const string& name, const int& cate);
	void start(shared_ptr<OptionInfo>& option_info, const int& sde_type, const int& rand_type, const int& fdm_type); // Start the whole program
};

#endif
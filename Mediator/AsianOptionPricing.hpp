/**
* Author: Zhixin Li
* File name: AsianOptionPricing.hpp
* Date: 2023.04.28
* Description: The header file for the mediator for the Asian options.
* Version: 1.0
* */

#ifndef ASIANOPTIONPRICING_HPP
#define ASIANOPTIONPRICING_HPP

#include "Mediator.hpp"
#include "AsianPricer.hpp"

template<typename T, template<typename T, typename Alloc> class Container = deque, typename Alloc = allocator<T>>
class AsianOptionPricing : public Mediator<T, Container, Alloc>
{
private:
	// CEV SDE
	double beta = 0;
	// CIR SDE
	double mean_reversion_rate = 0;
	double instant_rate = 0;

public:
	AsianOptionPricing(const int& sims, const int& step, const double& init_condition);
	virtual ~AsianOptionPricing();

	// Member functions
	const void insertUserMonitor(Observers<T, Container, Alloc>& obs, const string& name, const int& cate);
	void removeUser(const string& name, const int& cate);
	void start(shared_ptr<OptionInfo>& option_info, const int& sde_type, const int& rand_type, const int& fdm_type); // Start the whole program
};

#endif
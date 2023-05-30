/**
* Author: Zhixin Li
* File name: BarrierOptionPricing.hpp
* Date: 2023.05.06
* Description: The header file for the mediator for the Barrier options.
* Version: 1.0
* */

#ifndef BARRIEROPTIONPRICING_HPP
#define BARRIEROPTIONPRICING_HPP

#include "Mediator.hpp"

template<typename T, template<typename T, typename Alloc> class Container = deque, typename Alloc = allocator<T>>
class BarrierOptionPricing : public Mediator<T, Container, Alloc>
{
private:
	int barrier_type = 0; // 1 : knock-in barrier option; other : knock-out barrier option
	double barrier = 0; // The barrier price
	// CEV SDE
	double beta = 0;
	// CIR SDE
	double mean_reversion_rate = 0;
	double instant_rate = 0;

public:
	BarrierOptionPricing(const int& sims, const int& step, const double& init_condition);
	virtual ~BarrierOptionPricing();

	// Member functions
	const void insertUserMonitor(Observers<T, Container, Alloc>& obs, const string& name, const int& cate);
	void removeUser(const string& name, const int& cate);
	void start(shared_ptr<OptionInfo>& option_info, const int& sde_type, const int& rand_type, const int& fdm_type); // Start the whole program

	const void setBarrierType(const int& val);
	const void setBarrier(const double& val);
};

#endif
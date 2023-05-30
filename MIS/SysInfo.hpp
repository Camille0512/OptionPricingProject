/**
* Author: Zhixin Li
* File name: SysInfo.hpp
* Date: 2023.04.30
* Description: The header file for the message delivery.
* Version: 1.0
* */

#ifndef SYSINFO_HPP
#define SYSINFO_HPP

#include <memory>
#include "MIS.hpp"
#include "OptionInfo.hpp"

using std::shared_ptr;
using std::make_shared;

template<typename T, template<typename T, typename Alloc> class Container = deque, typename Alloc = allocator<T>>
class SysInfo : public MIS<T, Container, Alloc>
{
private:
	double option_theory_price; // The theoretical price of the option
	int option_info_counter; // Count the number of option observer observers
	int option_price_counter; // Count the number of option price observers

public:
	SysInfo(shared_ptr<OptionInfo>& option_ptr);
	virtual ~SysInfo();

	// Memeber functions
	void getOptionPrice(const double& price); // Get the option price from the mediator
	const void showCounter() const; // Return the current observer amount
	const void printOptionInfo(); // Discount the values from the future to the present
	const void printOptionPrice(); // Option pricing
	void removeObserver(); // Remove an observer
	shared_ptr<MIS<T, Container, Alloc>> transType(shared_ptr<SysInfo<T, Container, Alloc>>& ptr);
};

#endif
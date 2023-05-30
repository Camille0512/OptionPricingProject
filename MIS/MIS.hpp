/**
* Author: Zhixin Li
* File name: MIS.hpp
* Date: 2023.04.30
* Description: The header file for the manage information system.
* Version: 1.0
* */

#ifndef MIS_HPP
#define MIS_HPP

#include <memory>
#include <functional>
#include <deque>
#include "OptionInfo.hpp"
#include "MonteCarloSimulation.hpp"
#include "Observers.hpp"

using std::shared_ptr;
using std::function;
using std::deque;
using std::allocator;

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
class Observers;

template<typename T, template<typename T, typename Alloc> class Container = deque, typename Alloc = allocator<T>>
class MIS
{
public:
	using observer_types = function<void(shared_ptr<MIS<T, Container, Alloc>>)>; // Use function wrapper to wrap the observer function

	MIS(shared_ptr<OptionInfo>& option);
	virtual ~MIS();

	// Member functions
	void attach(observer_types func, const int& cate); // Adds an observer to the list
	void notify(); // Iterate to call every observers in the list

protected:
	shared_ptr<OptionInfo> option_info; // Data member

	int detach(); // Remove the observer

private:
	Container<observer_types, allocator<observer_types>> observers; // The container for all of the appended observers
	Container<int, allocator<int>> observer_cates; // The observer types
};

#endif
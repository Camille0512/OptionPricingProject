/**
* Author: Zhixin Li
* File name: Observers.hpp
* Date: 2023.04.15
* Description: The header file for the Observers class
* Version: 1.0
* */

#ifndef OBSERVERS_HPP
#define OBSERVERS_HPP

#include "MIS.hpp"
#include <memory>
#include <deque>
#include <functional>

using std::shared_ptr;
using std::deque;
using std::allocator;

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
class MIS; // Forward declaration

template<typename T, template<typename T, typename Alloc> class Container = deque, typename Alloc = allocator<T>>
class Observers
{
private:
	shared_ptr<MIS<T, Container, Alloc>> market_info; // Composition of the MIS and its derived classes
	long long id; // The create time of the observer

public:
	Observers();
	Observers(shared_ptr<MIS<T, Container, Alloc>> mis);
	~Observers();

	// Member functions
	void showOptionDetails();
	void showOptionPrice();
	long long getObserverID();
};

#endif
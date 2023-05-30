/**
* Author: Zhixin Li
* File name: Observers.cpp
* Date: 2023.04.15
* Description: The implementation file for the Observers class
* Version: 1.0
* */

#ifndef OBSERVERS_CPP
#define OBSERVERS_CPP

#include <chrono>
#include "Observers.hpp"
#include "SysInfo.cpp"

using std::chrono::system_clock;

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
Observers<T, Container, Alloc>::Observers() {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
Observers<T, Container, Alloc>::Observers(shared_ptr<MIS<T, Container, Alloc>> mis) : market_info(mis), id(system_clock::now().time_since_epoch().count()) {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
Observers<T, Container, Alloc>::~Observers() {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
void Observers<T, Container, Alloc>::showOptionDetails()
{
	auto sys_info = std::dynamic_pointer_cast<SysInfo<T, Container, Alloc>>(market_info);
	sys_info->printOptionInfo();
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
void Observers<T, Container, Alloc>::showOptionPrice()
{
	auto sys_info = std::dynamic_pointer_cast<SysInfo<T, Container, Alloc>>(market_info);
	sys_info->printOptionPrice();
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
long long Observers<T, Container, Alloc>::getObserverID() { return id; }

#endif
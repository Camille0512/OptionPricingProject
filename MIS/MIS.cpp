/**
* Author: Zhixin Li
* File name: MIS.cpp
* Date: 2023.05-01
* Description: The implementation file for the manage information system.
* Version: 1.0
* */

#ifndef MIS_CPP
#define MIS_CPP

#include "MIS.hpp"

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
MIS<T, Container, Alloc>::MIS(shared_ptr<OptionInfo>& option) : option_info(option) {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
MIS<T, Container, Alloc>::~MIS() {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
void MIS<T, Container, Alloc>::attach(observer_types func, const int& cate)
{
	observers.insert(observers.end(), func); // Input the observer function
	observer_cates.insert(observer_cates.end(), cate); // From which kind of observer
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
int MIS<T, Container, Alloc>::detach()
{
	observers.erase(observers.begin());
	int cate = observer_cates.erase(observer_cates.begin());
	return cate;
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
void MIS<T, Container, Alloc>::notify()
{
	for (auto& ptr : observers) ptr(this);
}

#endif
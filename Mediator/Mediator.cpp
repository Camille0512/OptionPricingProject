/**
* Author: Zhixin Li
* File name: Mediator.cpp
* Date: 2023.05.01
* Description: The implementation file for the builder mediator.
* Version: 1.0
* */

#ifndef MEDIATOR_CPP
#define MEDIATOR_CPP

#include "Mediator.hpp"

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
Mediator<T, Container, Alloc>::Mediator(const int& sims, const int& step, const double& init_condition) : n_sim(sims), steps(step), init_cond(init_condition) {};

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
Mediator<T, Container, Alloc>::~Mediator() {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
const void Mediator<T, Container, Alloc>::setBeta(const double& val) { beta = val; }

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
const void Mediator<T, Container, Alloc>::setMeanReversionRateNInstantRate(const double& rev_r, const double& inst_r)
{
	mean_reversion_rate = rev_r; instant_rate = inst_r;
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
const void Mediator<T, Container, Alloc>::setA(const double& val) { a = val; }

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
const void Mediator<T, Container, Alloc>::setB(const double& val) { b = val; }

#endif
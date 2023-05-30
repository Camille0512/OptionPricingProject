/**
* Author: Zhixin Li
* File name: Mediator.hpp
* Date: 2023.04.28
* Description: The header file for the builder mediator.
* Version: 1.0
* */

#ifndef MEDIATOR_HPP
#define MEDIATOR_HPP

#include <iostream>
#include <random>
#include <memory>
#include <deque>
#include <functional>
#include <map>
#include <string>
#include <tuple>
#include "OptionInfo.hpp"
#include "ISDE.hpp"
#include "FDMStrategy.hpp"
#include "MonteCarloSimulation.cpp"
#include "Pricer.cpp"
#include "MIS.cpp"
#include "SysInfo.cpp"
#include "Observers.cpp"

using std::cout;
using std::endl;
using std::deque;
using std::allocator;
using std::shared_ptr;
using std::make_shared;
using std::map;
using std::string;
using std::tuple;

template<typename T, template<typename T, typename Alloc> class Container = deque, typename Alloc = allocator<T>>
class Mediator
{
protected:
	int n_sim; // The number of simulations
	int steps;
	double init_cond;
	shared_ptr<OptionInfo> option;
	shared_ptr<FDMStrategy> fdm; // 0: Euler; 1: Milstein; 2: Predictor corrector; 3: Heun
	shared_ptr<MonteCarloSimulation<T, Container, Alloc>> mc;
	shared_ptr<Pricer<T, Container, Alloc>> pricer_pos; // Pricer for one side using z as random number
	shared_ptr<Pricer<T, Container, Alloc>> pricer_neg; // Pricer for the other side using -z as random number

	shared_ptr<SysInfo<T, Container, Alloc>> sys_info;
	// Observers are actually users; string: user name, int: observer type
	map<tuple<string, int>, Observers<T, Container, Alloc>> registered_users;

	// CEV SDE
	double beta = 0;
	// CIR SDE
	double mean_reversion_rate = 0;
	double instant_rate = 0;
	
	// FDM parameters
	double a;
	double b;

public:
	Mediator(const int& sims, const int& step, const double& init_condition);
	virtual ~Mediator();

	// Member functions
	virtual const void insertUserMonitor(Observers<T, Container, Alloc>& obs, const string& name, const int& cate) = 0;
	virtual void removeUser(const string& name, const int& cate) = 0;
	virtual void start(shared_ptr<OptionInfo>& option_info, const int& sde_type, const int& rand_type, const int& fdm_type) = 0; // Start the whole program

	virtual const void setBeta(const double& val) final;
	virtual const void setMeanReversionRateNInstantRate(const double& rev_r, const double& inst_r) final;
	virtual const void setA(const double& val) final;
	virtual const void setB(const double& val) final;
};

#endif
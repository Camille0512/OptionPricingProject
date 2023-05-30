/**
* Author: Zhixin Li
* File name: EuropeanOptionPricing.cpp
* Date: 2023.04.28
* Description: The implementaion file for the mediator for the European options.
* Version: 1.0
* */

#ifndef EUROPEANOPTIONPRICING_CPP
#define EUROPEANOPTIONPRICING_CPP

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <future>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <functional>
#include "Mediator.cpp"
#include "EuropeanOptionPricing.hpp"
#include "EulerFDM.hpp"
#include "MilsteinFDM.hpp"
#include "PredictorCorrectorFDM.hpp"
#include "HeunFDM.hpp"
#include "GBM.hpp"
#include "CEV.hpp"
#include "CIR.hpp"
#include "IRNG.hpp"
#include "VanillaPricer.cpp"
#include "StopWatch.hpp"
#include <chrono>
#include <omp.h>

using std::cout;
using std::endl;
using std::cin;
using std::map;
using std::string;
using std::tuple;
using std::make_tuple;
using std::tie;
using std::future;
using std::async;
using std::packaged_task;
using std::vector;
using std::for_each;
using std::unique_lock;
using std::thread;
using std::chrono::seconds;
using std::function;
using std::placeholders::_1;
using std::placeholders::_2;
using std::bind;

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
EuropeanOptionPricing<T, Container, Alloc>::EuropeanOptionPricing(const int& sims, const int& step, const double& init_condition) : 
	Mediator<T, Container, Alloc>(sims, step, init_condition) {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
EuropeanOptionPricing<T, Container, Alloc>::~EuropeanOptionPricing() {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
const void EuropeanOptionPricing<T, Container, Alloc>::insertUserMonitor(Observers<T, Container, Alloc>& obs, const string& name, const int& cate)
{
	tuple<string, int> user_info = make_tuple(name, cate);
	this->registered_users[user_info] = obs; // Once there are uninitialized base class data members, should be called using "this->"
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
void EuropeanOptionPricing<T, Container, Alloc>::removeUser(const string& name, const int& cate)
{
	tuple<string, int> user_info = make_tuple(name, cate);
	this->registered_users.erase(user_info);
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
void EuropeanOptionPricing<T, Container, Alloc>::start(shared_ptr<OptionInfo>& option_info, const int& sde_type, const int& rand_type, const int& fdm_type)
{
	StopWatch watch; watch.StartStopWatch(); // Timer
	this->option = option_info;
	
	// Choose SDE
	shared_ptr<ISDE> sde;
	switch (sde_type)
	{
		case 0:
		{
			sde = make_shared<GBM>(this->option, this->init_cond); break;
		}
		case 1:
		{
			if (this->beta == 0) { cout << "[Warning] You may have forgotten to set the beta value." << endl; }
			sde = make_shared<CEV>(this->option, this->beta, this->init_cond); break;
		}
		case 2:
		{
			if (this->mean_reversion_rate == 0 && this->instant_rate) { cout << "[Warning] You may have forgotten to set the parameter values." << endl; }
			sde = make_shared<CIR>(this->option, this->mean_reversion_rate, this->instant_rate, this->init_cond); break;
		}
		default:
		{
			cout << "[Error] Wrong input sde_type." << endl;
		}
	}
	
	// Choose random number generator
	IRNG rand; function<vector<double>(const int&, const int&)> rand_func;
	switch (rand_type)
	{ // 0: Normal distritbution; 1: Polar Marsaglia Net; 2: Box Muller Net
		case 0:
		{
			rand_func = bind(&IRNG::genNormalRNG, rand, _1, _2); break;
		}
		case 1:
		{
			rand_func = bind(&IRNG::genPolarMarsagliaNetRNG, rand, _1, _2); break;
		}
		case 2:
		{
			rand_func = bind(&IRNG::genBoxMullerNetRNG, rand, _1, _2); break;
		}
		default:
		{
			cout << "[Error] Wrong input rand_type." << endl;
		}
	}
	
	// Choose fdm
	shared_ptr<FDMStrategy> fdm_ptr;
	switch (fdm_type)
	{
		case 0:
		{
			fdm_ptr = make_shared<EulerFDM>(sde, this->steps); break;
		}
		case 1:
		{
			fdm_ptr = make_shared<MilsteinFDM>(sde, this->steps); break;
		}
		case 2:
		{
			if (this->a == 0 && this->b == 0) cout << "[Warning] Please check whether you have initialize the coefficient a and b." << endl;
			fdm_ptr = make_shared<PredictorCorrectorFDM>(sde, this->steps, this->a, this->b); break;
		}
		case 3:
		{
			fdm_ptr = make_shared<HeunFDM>(sde, this->steps); break;
		}
		default:
		{
			cout << "[Error] Wrong input fdm_type." << endl;
		}
	}
	this->fdm = fdm_ptr;

	watch.StopStopWatch(); // Stop the timer
	double time1 = watch.GetTime(); // Get the program running time
	cout << "===== [TIMER 1] =====\n" << time1 << endl;
	watch.Reset(); watch.StartStopWatch();

	// The lambda function for the concurrency
	int scale = 1000; double option_price = 0;

	std::mutex m_mutex;
	auto func = [&](int seed) {
		unique_lock<std::mutex> lock(m_mutex);
		for (int j = 0; j < scale; j++)
		{
			// Monte Carlo Simulation - with antithetic variance reduction technique
			this->mc = make_shared<MonteCarloSimulation<T, Container, Alloc>>(this->option);
			this->mc->genPath(rand_func, this->fdm, seed + 100 * j);
			Container<T, Alloc> path1, path2; tie(path1, path2) = this->mc->getMesh();

			// Set Pricer
			this->pricer_pos = make_shared<VanillaPricer<T, Container, Alloc>>(path1, this->option);
			T option_price1 = this->pricer_pos->pricing(); option_price += option_price1;
			this->pricer_neg = make_shared<VanillaPricer<T, Container, Alloc>>(path2, this->option);
			T option_price2 = this->pricer_neg->pricing(); option_price += option_price2;
		}
		lock.unlock();
	};

	
	watch.StopStopWatch(); // Stop the timer
	double time2 = watch.GetTime(); // Get the program running time
	cout << "===== [TIMER 2] =====\n" << time2 << endl;
	watch.Reset(); watch.StartStopWatch();

	/* Using sequence 
	for (int i = 0; i < (this->n_sim / scale); i++)
	{
		const int seed = 1234 + 101 * i;
		func(seed);
	}*/
	
	/* Multi-threading */
	vector<thread> vec_thread;
	for (int i = 0; i < (this->n_sim / scale); i++)
	{
		vec_thread.push_back(thread(func, 1234 + 101 * i));
	}
	for (auto& t : vec_thread) { t.join(); }

	/* OpenMP 
	omp_set_num_threads(16);
	#pragma omp parallel for
	for (auto i = 0; i < (this->n_sim / scale); i++)
	{
		func(1234 + 101 * i);
	}*/

	option_price /= this->n_sim; // Average the price


	watch.StopStopWatch(); // Stop the timer
	double time3 = watch.GetTime(); // Get the program running time
	cout << "===== [TIMER 3] =====\n" << time3 << endl;
	watch.Reset(); watch.StartStopWatch();

	// Observe information
	this->sys_info = make_shared<SysInfo<T, Container, Alloc>>(this->option);
	shared_ptr<MIS<T, Container, Alloc>> mis = this->sys_info->transType(this->sys_info);
	Observers<T, Container, Alloc> obs(mis); // Create one observer
	insertUserMonitor(obs, "User01", 0); insertUserMonitor(obs, "User01", 1);
	
	this->sys_info->getOptionPrice(option_price);
	
	for (auto& [k, v] : this->registered_users)
	{
		string name; int cate; tie(name, cate) = k;
		switch(cate)
		{
			case 0:
			{
				this->sys_info->attach([&v](shared_ptr<MIS<T, Container, Alloc>> ptr) { v.showOptionDetails(); }, 0);
				v.showOptionDetails(); cout << endl;  break;
			}
			case 1:
			{
				this->sys_info->attach([&v](shared_ptr<MIS<T, Container, Alloc>> ptr) { v.showOptionPrice(); }, 1);
				v.showOptionPrice(); cout << endl;  break;
			}
			default: break;
		}
	}

	watch.StopStopWatch(); // Stop the timer
	double time = watch.GetTime(); // Get the program running time
	cout << "It took " << (time + time1 + time2 + time3) / 1000 << " seconds to run the program.." << endl;
}

#endif
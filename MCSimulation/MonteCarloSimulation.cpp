/**
* Author: Zhixin Li
* File name: MonteCarloSimulation.hpp
* Date: 2023.04.30
* Description: The implementation file for the Monte Carlo simulation with antithetic variance reduction technique to simulate the price paths.
* Version: 1.0
* */

#ifndef MONTECARLOSIMULATION_CPP
#define MONTECARLOSIMULATION_CPP

#include "MonteCarloSimulation.hpp"

#include <iostream>
#include <thread>
#include <mutex>

using std::make_tuple;
using std::unique_lock;

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
MonteCarloSimulation<T, Container, Alloc>::MonteCarloSimulation() :
	option(make_shared<OptionInfo>()) {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
MonteCarloSimulation<T, Container, Alloc>::MonteCarloSimulation(shared_ptr<OptionInfo>& option) : 
	option(option) {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
MonteCarloSimulation<T, Container, Alloc>::~MonteCarloSimulation() {}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
void MonteCarloSimulation<T, Container, Alloc>::genPath(function<vector<double>(const int&, const int&)> rand, shared_ptr<FDMStrategy>& fdm_method, const int& seed_val)
{ // Fill in the mesh with generated underlying asset price path
	double cur_price1 = option->getUnderlyingPrice(); double cur_price2 = cur_price1;
	mesh_pos.push_back(cur_price1); // Initial value for the mesh
	mesh_neg.push_back(cur_price2); // Initial value for the mesh
	double dt = fdm_method->getDeltaT();
	int steps = fdm_method->getSteps(); int denorminator = steps / 100;

	vector<double> z_vec = rand(steps, seed_val); // Generate the random number for mimicing the Winner Process

	//std::mutex m_mutex;
	for (int i = 0; i < steps; i++)
	{
		double z = z_vec[i];
		double new_price1 = fdm_method->compute(cur_price1, dt, z, z);
		mesh_pos.push_back(new_price1); // Put into the mesh
		cur_price1 = new_price1; // Update the current price

		double new_price2 = fdm_method->compute(cur_price2, dt, -z, -z);
		mesh_neg.push_back(new_price2); // Put into the mesh
		cur_price2 = new_price2; // Update the current price
	}
}

template<typename T, template<typename T, typename Alloc> class Container, typename Alloc>
tuple<Container<T, Alloc>, Container<T, Alloc>> MonteCarloSimulation<T, Container, Alloc>::getMesh()
{
	return make_tuple(mesh_pos, mesh_neg);
}

#endif
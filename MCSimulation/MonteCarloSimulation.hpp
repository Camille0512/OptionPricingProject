/**
* Author: Zhixin Li
* File name: MonteCarloSimulation.hpp
* Date: 2023.04.30
* Description: The header file for the Monte Carlo simulation with antithetic variance reduction technique to simulate the price paths.
* Version: 1.0
* */

#ifndef MONTECARLOSIMULATION_HPP
#define MONTECARLOSIMULATION_HPP

#include <vector>
#include <memory>
#include <deque>
#include <tuple>
#include <functional>
#include "FDMStrategy.hpp"
#include "OptionInfo.hpp"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::deque;
using std::allocator;
using std::tuple;
using std::function;

// TODO: Maybe can make it a Singleton
template<typename T, template<typename T, typename Alloc> class Container = deque, typename Alloc = allocator<T>>
class MonteCarloSimulation
{
private:
	//shared_ptr<NormalRNG> rand; // 0: Normal distritbution; 1: Polar Marsaglia Net; 2: Box Muller Net
	shared_ptr<OptionInfo> option;
	Container<T, Alloc> mesh_pos;
	Container<T, Alloc> mesh_neg;

public:
	MonteCarloSimulation();
	MonteCarloSimulation(shared_ptr<OptionInfo>& option);
	virtual ~MonteCarloSimulation();

	// Member functions
	void genPath(function<vector<double>(const int&, const int&)> rand, shared_ptr<FDMStrategy>& fdm_method, const int& seed_val); // Fill in the mesh with generated underlying asset price path
	tuple<Container<T, Alloc>, Container<T, Alloc>> getMesh(); // Return the path
};

#endif
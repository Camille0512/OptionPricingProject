/**
* Author: Zhixin Li
* File name: IRNG.hpp
* Date: 2023.04.29
* Description: The header file for the random number generator.
* Version: 1.0
* 
* Modification:
* 2023.05.07 Add more random number generating functions
* */

#ifndef IRNG_HPP
#define IRNG_HPP

#include <random>
#include <vector>

using std::normal_distribution;
using std::vector;

class IRNG
{
private:
	std::mt19937_64 engine; // Mersenne Twister engin
	normal_distribution<double> rand;

public:
	IRNG();
	virtual ~IRNG();

	// Must generate a sequence of random number so that these numbers all obeys the same one distribution
	vector<double> genNormalRNG(const int& vec_size, const int& seed);
	vector<double> genPolarMarsagliaNetRNG(const int& vec_size, const int& seed);
	vector<double> genBoxMullerNetRNG(const int& vec_size, const int& seed);
};

#endif
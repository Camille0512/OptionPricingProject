/**
* Author: Zhixin Li
* File name: IRNG.cpp
* Date: 2023.04.29
* Description: The implementation file for the random number generator.
* Version: 1.0
* */

#define _USE_MATH_DEFINES
#include <math.h>

#ifndef IRNG_CPP
#define IRNG_CPP

#include "IRNG.hpp"

IRNG::IRNG() {}

IRNG::~IRNG() {}

vector<double> IRNG::genNormalRNG(const int& vec_size, const int& seed)
{ // Given the same seed and vector size will always generate the same sequence of random numbers
	engine.seed(seed);

	vector<double> rand_vec; // A vector of random numbers
	for (int i = 0; i < vec_size; i++)
	{
		rand_vec.push_back(rand(engine));
	}

	return rand_vec;
}

vector<double> IRNG::genPolarMarsagliaNetRNG(const int& vec_size, const int& seed)
{ // Given the same seed and vector size will always generate the same sequence of random numbers
	engine.seed(seed);

	vector<double> rand_vec; // A vector of random numbers
	for (int i = 0; i < vec_size; i++)
	{
		double u, v, S;
		do
		{
			u = 2.0 * rand(engine) - 1.0;
			v = 2.0 * rand(engine) - 1.0;
			S = pow(u, 2) + pow(v, 2);
		} while (S > 1.0 || S <= 0.0);

		double fac = sqrt(-2.0 * log(S) / S);
		rand_vec.push_back(fac * u);
	}

	return rand_vec;
}

vector<double> IRNG::genBoxMullerNetRNG(const int& vec_size, const int& seed)
{ // Given the same seed and vector size will always generate the same sequence of random numbers
	engine.seed(seed);

	vector<double> rand_vec; // A vector of random numbers
	for (int i = 0; i < vec_size; i++)
	{
		double u, v;
		do
		{
			u = rand(engine);
			v = rand(engine);
		} while (u <= 0.0);

		double fac = sqrt(-2.0 * log(u)) * cos(2.0 * M_PI * v);
		rand_vec.push_back(fac);
	}

	return rand_vec;
}

#endif
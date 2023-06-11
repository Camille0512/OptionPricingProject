/**
* Author: Zhixin Li
* File name: main.cpp
* Date: 2023.04.29
* Description: The run script for final project
* Version: 1.0
* */

#include <iostream>
#include <random>
#include <memory>
#include <numeric>
#include "IRNG.cpp"
#include "OptionInfo.cpp"
#include "FDMStrategy.cpp"
#include "EulerFDM.cpp"
#include "HeunFDM.CPP"
#include "MilsteinFDM.cpp"
#include "PredictorCorrectorFDM.cpp"
#include "ISDE.cpp"
#include "GBM.cpp"
#include "CEV.cpp"
#include "CIR.cpp"
#include "EuropeanOptionPricing.cpp"
#include "AsianOptionPricing.cpp"
#include "BarrierOptionPricing.cpp"
using std::cout;
using std::endl;
using std::cin;
using std::shared_ptr;
using std::make_shared;
using std::pow;

int main()
{
	// OptionInfo variables
	double asset_price;
	double strike;
	double expiry;
	double ir;
	double volatility;
	double dividend;
	int option_type;
	double init_cond;
	int steps;
	int n_sims;

	{
		// User interactive process
		cout << "Use default mode (0), self-defined option mode (1): ";
		//int num; cin >> num;
		int num = 0; // TODO: Remove this

		if (num == 0)
		{
			asset_price = 102; strike = 100; expiry = 0.5; ir = 0.03; volatility = 0.3; dividend = 0.01;
			option_type = 1; init_cond = 0; steps = 300; //n_sims = 50000;
			steps = 4; // Use 4 simluations to test
		}
		else
		{
			cout << "Please enter the underlying asset price: "; cin >> asset_price; cout << endl;
			cout << "Please enter the strike price: "; cin >> strike; cout << endl;
			cout << "Please enter the time to maturity: "; cin >> expiry; cout << endl;
			cout << "Please enter the interest rate: "; cin >> ir; cout << endl;
			cout << "Please enter the volatility: "; cin >> volatility; cout << endl;
			cout << "Please enter the dividend: "; cin >> dividend; cout << endl;
			cout << "Please enter the option type: "; cin >> option_type; cout << endl;
			cout << "Please enter the initial condition: "; cin >> init_cond; cout << endl;
			cout << "Please enter the steps: "; cin >> steps; cout << endl;
		}

		shared_ptr<OptionInfo> call(new OptionInfo(asset_price, strike, expiry, ir, volatility, dividend, option_type));

		// European options
		cout << "==================== European options ====================" << endl;
		EuropeanOptionPricing<double, vector, allocator<double>> european(n_sims, steps, init_cond);
		cout << "*** European option pricing using GBM SDE ***" << endl;
		european.start(call, 0, 0, 0); cout << endl;
		/*
		cout << "*** European option pricing using CEV SDE ***" << endl;
		double beta = 0.8; european.setBeta(beta);
		european.start(call, 1, 0, 0); cout << endl;

		cout << "*** European option pricing using CIR SDE ***" << endl;
		double revert_r = 0.3; double inst_r = 0.025; european.setMeanReversionRateNInstantRate(revert_r, inst_r);
		european.start(call, 2, 0, 0); cout << endl;

		cout << "*** European option pricing using GBM SDE & Euler FDM ***" << endl;
		european.start(call, 0, 0, 0); cout << endl;

		cout << "*** European option pricing using GBM SDE & Milstein FDM ***" << endl;
		european.start(call, 0, 0, 1); cout << endl;

		cout << "*** European option pricing using GBM SDE & Predictor Corrector FDM ***" << endl;
		european.setA(0.5); european.setB(0.8);
		european.start(call, 0, 0, 2); cout << endl;

		cout << "*** European option pricing using GBM SDE & Heun FDM ***" << endl;
		european.start(call, 0, 0, 3); cout << endl;


		// Asian options
		cout << "==================== Asian options ====================" << endl;
		AsianOptionPricing<double, vector, allocator<double>> asian(n_sims, steps, init_cond);
		cout << "*** Asian option pricing using GBM SDE ***" << endl;
		asian.start(call, 0, 0, 0); cout << endl;

		cout << "*** Asian option pricing using CEV SDE ***" << endl;
		asian.setBeta(beta);
		asian.start(call, 1, 0, 0); cout << endl;

		cout << "*** Asian option pricing using CIR SDE ***" << endl;
		asian.setMeanReversionRateNInstantRate(revert_r, inst_r);
		asian.start(call, 2, 0, 0); cout << endl;

		cout << "*** Asian option pricing using GBM SDE ***" << endl;
		asian.start(call, 0, 0, 0); cout << endl;

		cout << "*** Asian option pricing using GBM SDE & Milstein FDM ***" << endl;
		asian.start(call, 0, 0, 1); cout << endl;

		cout << "*** Asian option pricing using GBM SDE & Predictor Corrector FDM ***" << endl;
		asian.setA(0.5); asian.setB(0.8);
		asian.start(call, 0, 0, 2); cout << endl;

		cout << "*** Asian option pricing using GBM SDE & Heun FDM ***" << endl;
		asian.start(call, 0, 0, 3); cout << endl;


		// Barrier options
		cout << "==================== Barrier options ====================" << endl;
		BarrierOptionPricing<double, vector, allocator<double>> barrier(n_sims, steps, init_cond);
		barrier.setBarrierType(1); barrier.setBarrier(110);
		cout << "*** Barrier option pricing using GBM SDE ***" << endl;
		barrier.start(call, 0, 0, 0); cout << endl;

		cout << "*** Barrier option pricing using CEV SDE ***" << endl;
		barrier.setBeta(beta);
		barrier.start(call, 1, 0, 0); cout << endl;

		cout << "*** Barrier option pricing using CIR SDE ***" << endl;
		barrier.setMeanReversionRateNInstantRate(revert_r, inst_r);
		barrier.start(call, 2, 0, 0); cout << endl;

		barrier.setBarrierType(1); barrier.setBarrier(110);
		cout << "*** Barrier option pricing using GBM SDE ***" << endl;
		barrier.start(call, 0, 0, 0); cout << endl;

		cout << "*** Barrier option pricing using GBM SDE & Milstein FDM ***" << endl;
		barrier.start(call, 0, 0, 1); cout << endl;

		cout << "*** Barrier option pricing using GBM SDE & Predictor Corrector FDM ***" << endl;
		barrier.setA(0.5); barrier.setB(0.8);
		barrier.start(call, 0, 0, 2); cout << endl;

		cout << "*** Barrier option pricing using GBM SDE & Heun FDM ***" << endl;
		barrier.start(call, 0, 0, 3); cout << endl;*/
	}
	/*
	{ // Edge case
		cout << "*** ===== *** Edge case *** ===== ***" << endl;
		{
			asset_price = 0; strike = 100; expiry = 0.5; ir = 0.03; volatility = 0.3; dividend = 0.01;
			option_type = 1; init_cond = 0; steps = 300; n_sims = 50000;

			shared_ptr<OptionInfo> call(new OptionInfo(asset_price, strike, expiry, ir, volatility, dividend, option_type));

			cout << "==================== European options ====================" << endl;
			EuropeanOptionPricing<double, vector, allocator<double>> european(n_sims, steps, init_cond);
			cout << "*** European option pricing using GBM SDE ***" << endl;
			european.start(call, 0, 0, 0); cout << endl;
		}
		
		{
			asset_price = 102; strike = 0; expiry = 0.5; ir = 0.03; volatility = 0.3; dividend = 0.01;
			option_type = 1; init_cond = 0; steps = 300; n_sims = 50000;

			shared_ptr<OptionInfo> call(new OptionInfo(asset_price, strike, expiry, ir, volatility, dividend, option_type));

			cout << "==================== European options ====================" << endl;
			EuropeanOptionPricing<double, vector, allocator<double>> european(n_sims, steps, init_cond);
			cout << "*** European option pricing using GBM SDE ***" << endl;
			european.start(call, 0, 0, 0); cout << endl;
		}

		{
			asset_price = 102; strike = 100; expiry = 0; ir = 0.03; volatility = 0.3; dividend = 0.01;
			option_type = 1; init_cond = 0; steps = 300; n_sims = 50000;

			shared_ptr<OptionInfo> call(new OptionInfo(asset_price, strike, expiry, ir, volatility, dividend, option_type));

			cout << "==================== European options ====================" << endl;
			EuropeanOptionPricing<double, vector, allocator<double>> european(n_sims, steps, init_cond);
			cout << "*** European option pricing using GBM SDE ***" << endl;
			european.start(call, 0, 0, 0); cout << endl;
		}
	}*/
	
	return 0;
}
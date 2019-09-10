/*
	Copyright (c) 2019, Daniel Hanson
	University of Washington
	Dept of Applied Mathematics
	Computational Finance & Risk Management (CFRM)
	For instructional purposes only
*/

#include "MonteCarloOptions/EquityPriceGenerator.h"
#include "MonteCarloOptions/MCEuroOptPricer.h"
#include "ExampleFunctionsHeader.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <execution>
#include <ctime>

using std::vector;
using std::cout;
using std::endl;
using std::for_each;

void equityScenarioTest(double initEquityPrice, unsigned numTimeSteps, double timeToMaturity, 
	double riskFreeRate, double volatility, int seed);
void printDouble(double x);
void mcOptionTestNotParallel();
void mcOptionTestRunParallel();
void transformPar(size_t n, int terms, int seed);

int main()
{
	double initEquityPrice = 100.0;
	unsigned numTimeSteps = 12;		// 5 years, quarterly time steps
	double timeToMaturity = 1.0;	

	double drift = 0.025;			// risk-free interest rate
	double volatility = 0.06;	
	int seed = -106;
	equityScenarioTest(initEquityPrice, numTimeSteps, timeToMaturity, drift, volatility, seed);

	mcOptionTestNotParallel();
	mcOptionTestRunParallel();

	// Parallel STL Algorithms:
/*	transformPar(5000000, 400, 106);	// num variates, num series terms, seed
	transformPar(5000000, 400, -106);	*/

	// Warning: These can take a long time on a basic laptop...
/*	transformPar(50000000, 200, 5863);
	transformPar(50000000, 200, -5863);

	transformPar(100000000, 200, 874);
	transformPar(100000000, 200, -874);*/

	// Call root finding examples:
//	bisectionExamples();
//	steffensonExamples();

	// Call Boost examples:
	// Numerical differentiation:
//	finiteDifferences();

	// Numerical integration:
//	trapezoidal();

	// Circular Buffers
//	simple_example();
//	time_series_example();

	// Accumulators
/*	minMaxAccumulator();
	meanAndVarAccumulator();
	vectorAndAccumulator();  */

	// MultiArray example:
//	TestLattice();

	return 0;
}

void equityScenarioTest(double initEquityPrice, unsigned numTimeSteps, double timeToMaturity, 
						double riskFreeRate, double volatility, int seed)
{
	cout << "-----  equityScenarioTest(.), seed = " << seed << " -----" << endl;


	// EquityPriceGenerator(double initEquityPrice, unsigned numTimeSteps, double timeToMaturity, double drift, double volatility);
	EquityPriceGenerator epg(initEquityPrice, numTimeSteps, timeToMaturity, riskFreeRate, volatility);
	vector<double> synPrices = epg(seed);

	for_each(synPrices.begin(), synPrices.end(), printDouble);
	cout << endl << endl;
}

void mcOptionTestNotParallel()
{
	cout << endl << "--- mcOptionTestNotParallel(.) ---" << endl;
	double strike = 102.0;
	double spot = 100.0;
	double riskFreeRate = 0.025;
	double volatility = 0.06;
	double tau = 10.0;
	double quantity = 7000.00;	// 1.0;
	OptionType call = OptionType::CALL;
	int numTimeSteps = 1200;
	int numScenarios = 100000;
	int initSeed = 100;

	/*
		// Constructor signature:
		MCEuroOptPricer(double strike, double spot, double riskFreeRate, double volatility,
		double tau, OptionType optionType, int numTimeSteps, int numScenarios, 
		bool runParallel, int initSeed, double quantity);
	*/

	MCEuroOptPricer qlCall(strike, spot, riskFreeRate, volatility, tau,
		call, numTimeSteps, numScenarios, false, initSeed, quantity);
	double res = qlCall();	
	cout << "Runtime (NOT in parallel) = " << qlCall.time() << "; price = " << res << endl << endl;
}

void mcOptionTestRunParallel()
{
	cout << endl << "--- mcOptionTestRunParallel(.) ---" << endl;
	double strike = 102.0;
	double spot = 100.0;
	double riskFreeRate = 0.025;
	double volatility = 0.06;
	double tau = 10.0;
	double quantity = 7000.00;	// 1.0;  (Number of contracts)
	OptionType call = OptionType::CALL;
	int numTimeSteps = 1200;
	int numScenarios = 100000;
	int initSeed = 100;

	MCEuroOptPricer qlCall(strike, spot, riskFreeRate, volatility, tau,
		call, numTimeSteps, numScenarios, true, initSeed, quantity);
	
	double res = qlCall();
	cout << "Runtime (IS RUN in parallel) = " << qlCall.time() << "; price = " << res << endl << endl;
}


void printDouble(double x)
{
	cout << x << " ";
}

// For testing parallel STL algorithm transform(.):
void transformPar(size_t n, int terms, int seed)
{
	cout << endl << "--- transformPar(.) ---" << endl;
	std::mt19937_64 mtre(seed);
	std::normal_distribution<> nd;
	vector<double> v(n);

	auto nextNorm = [&mtre, &nd](double x)
	{
		return nd(mtre);
	};

	std::transform(v.begin(), v.end(), v.begin(), nextNorm);
	auto u = v;

	cout << endl;

	auto expSeries = [terms](double x) {
		double num = x;
		double den = 1.0;
		double res = 1.0 + x;
		for (int k = 2; k < terms; ++k)
		{
			num *= x;
			den *= static_cast<double>(k);
			res += num / den;
		}
		return res;
	};

	cout << "Sanity check: " << endl;
	cout << "exp(0) = " << expSeries(0.0) << " - should = 1.0" << endl;
	cout << "exp(1) = " << expSeries(1.0) << " - should = 2.71828" << endl << endl;

	// Use std::transform to run exponential power series on each element in v:
	clock_t begin = clock();		// begin time with threads
	std::transform(u.begin(), u.end(), u.begin(), expSeries);
	clock_t end = clock();		// end transform time with no par
	auto time = (end - begin) / CLOCKS_PER_SEC;

	auto mean = (1.0 / u.size())*std::reduce(u.cbegin(), u.cend(), 0.0);

	cout << "Time required for serialized calculations = "
		<< time << " seconds." << endl;
	cout << "Mean exponential value = " << mean << endl << endl;


	// Use std::transform with std::par execution policy 
	// to run exponential power series on each element in v:
	begin = clock();		// begin time with threads
	std::transform(std::execution::par, v.begin(), v.end(), v.begin(), expSeries);
	end = clock();		// end transform time with par
	time = (end - begin) / CLOCKS_PER_SEC;

	auto meanPar = (1.0 / v.size())*std::reduce(v.cbegin(), v.cend(), 0.0);

	cout << "Time required for parallel algorithm calculations = "
		<< time << " seconds." << endl;
	cout << "Mean exponential value (par) = " << meanPar << endl << endl;
}


/*
	Unless explicitly acquired and licensed from Licensor under another
	license, the contents of this file are subject to the Reciprocal Public
	License ("RPL") Version 1.5, or subsequent versions as allowed by the RPL,
	and You may not copy or use this file in either source code or executable
	form, except in compliance with the terms and conditions of the RPL.

	All software distributed under the RPL is provided strictly on an "AS
	IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND
	LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
	LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
	PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the RPL for specific
	language governing rights and limitations under the RPL.
*/
/*
	Copyright (c) 2019, Daniel Hanson
	University of Washington
	Dept of Applied Mathematics
	Computational Finance & Risk Management (CFRM)
*/

#ifndef MC_EURO_OPT_PRICER_H
#define MC_EURO_OPT_PRICER_H

#include "EquityPriceGenerator.h"
enum class OptionType
{
	CALL,
	PUT
};

class MCEuroOptPricer
{
public:
	MCEuroOptPricer(double strike, double spot, double riskFreeRate, double volatility,
		double timeToExpiry, OptionType optionType, int numTimeSteps, int numScenarios,
		bool runParallel, int initSeed, double quantity);

	double operator()() const;
	double time() const;		// Time required to run calcutions (for comparison using concurrency)

private:
	void calculate_();			// Start calculation of option price

	// Private helper functions:
	void computePrice_();
	void generateSeeds_();
	double payoff_(double terminalPrice);

	// Compare results:  non-parallel vs in-parallel with async and futures
	void computePriceNoParallel_();
	void computePriceAsync_();

	// Inputs to model:
	double strike_;
	double spot_;
	double riskFreeRate_;
	double volatility_;
	double timeToExpiry_;	// Time to expiration (as year fraction)
	OptionType porc_;		// porc_: put or call
	int numTimeSteps_;	
	int numScenarios_;
	bool runParallel_ = true;
	int initSeed_ = 106;	// Initial seed setting
	double quantity_ = 1.0;	// Number of contracts

	// Computed values:
	double discFactor_;
	double price_;

	// Vector storing generated seeds for the MC scenarios:
	std::vector<int> seeds_;

	// Runtime comparison using concurrency
	double time_;
};

#endif

/*
	Copyright 2019 Daniel Hanson

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

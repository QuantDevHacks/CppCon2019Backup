/*
	Copyright (c) 2019, Daniel Hanson
	University of Washington
	Dept of Applied Mathematics
	Computational Finance & Risk Management (CFRM)
	For instructional purposes only
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

/*
	Copyright (c) 2019, Daniel Hanson
	University of Washington
	Dept of Applied Mathematics
	Computational Finance & Risk Management (CFRM)
	For instructional purposes only
*/

#include "MCEuroOptPricer.h"
#include "EquityPriceGenerator.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <future>
#include <ctime>
#include <limits>

MCEuroOptPricer::MCEuroOptPricer(double strike, double spot, double riskFreeRate, double volatility,
	double timeToExpiry, OptionType porc, int numTimeSteps, int numScenarios,
	bool runParallel, int initSeed, double quantity) :strike_(strike), spot_(spot),
	riskFreeRate_(riskFreeRate), volatility_(volatility), timeToExpiry_(timeToExpiry), porc_(porc),
	numTimeSteps_(numTimeSteps), numScenarios_(numScenarios), runParallel_(runParallel),
	initSeed_(initSeed), quantity_(quantity)
{
	discFactor_ = std::exp(-riskFreeRate_ * timeToExpiry_);
	calculate_();
}

double MCEuroOptPricer::operator()() const
{
	return price_;
}

double MCEuroOptPricer::time() const
{
	return time_;
}

void MCEuroOptPricer::calculate_()
{
	std::clock_t begin = std::clock();		// begin time with threads
	computePrice_();
	std::clock_t end = std::clock();		// end time with threads
	time_ = double(end - begin) / CLOCKS_PER_SEC;
}

// Private helper functions:
void MCEuroOptPricer::computePrice_()
{
	if (runParallel_)
	{
		computePriceAsync_();			
	}
	else
	{
		computePriceNoParallel_();		
	}
}

void MCEuroOptPricer::computePriceNoParallel_()
{
	EquityPriceGenerator epg(spot_, numTimeSteps_, timeToExpiry_, riskFreeRate_, volatility_);
	generateSeeds_();
	std::vector<double> discountedPayoffs;
	discountedPayoffs.reserve(numScenarios_);

	for (auto& seed : seeds_)
	{
		double terminalPrice = (epg(seed)).back();
		double payoff = payoff_(terminalPrice);

		discountedPayoffs.push_back(discFactor_ * payoff);
	}

	// numScenarios_ should = discountedPayoffs.size()
	double numScens = static_cast<double>(numScenarios_);
	price_ = quantity_ * (1.0 / numScens) * 
		std::accumulate(discountedPayoffs.begin(), discountedPayoffs.end(), 0.0);
}

void MCEuroOptPricer::computePriceAsync_()
{
	EquityPriceGenerator epg(spot_, numTimeSteps_, timeToExpiry_, riskFreeRate_, volatility_);
	generateSeeds_();

	using realVector = std::vector<double>;		
	std::vector<std::future<realVector> > futures;
	futures.reserve(numScenarios_);

	for (auto& seed : seeds_)
	{
		futures.push_back(std::async(epg, seed));
	}

	realVector discountedPayoffs;
	discountedPayoffs.reserve(numScenarios_);

	for (auto& future : futures)
	{
		double terminalPrice = future.get().back();		
		double payoff = payoff_(terminalPrice);
		discountedPayoffs.push_back(discFactor_ * payoff);
	}

	double numScens = static_cast<double>(numScenarios_);
	price_ = quantity_ * (1.0 / numScens) *
		std::accumulate(discountedPayoffs.begin(), discountedPayoffs.end(), 0.0);
}

void MCEuroOptPricer::generateSeeds_()
{
	seeds_.resize(numScenarios_);

	// This is a contrived way of setting a different seed for 
	// each scenario.  There are more robust ways to do this if desired.
	std::iota(seeds_.begin(), seeds_.end(), initSeed_);
}

double MCEuroOptPricer::payoff_(double terminalPrice)
{
	double payoff = 0.0;
	switch (porc_)
	{
	case OptionType::CALL:
		payoff = std::max(terminalPrice - strike_, 0.0);
		break;
	case OptionType::PUT:
		payoff = std::max(strike_ - terminalPrice, 0.0);
		break;
	default:	// This case should NEVER happen
		payoff = std::numeric_limits<double>::quiet_NaN();
		break;
	}
	return payoff;
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
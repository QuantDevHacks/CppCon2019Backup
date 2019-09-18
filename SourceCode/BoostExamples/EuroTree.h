#ifndef EURO_TREE_H
#define EURO_TREE_H

#include <boost/multi_array.hpp>
#include "Node.h"
// #include "Date.h"
// #include "DayCount.h"

class EuroTree
{
public:
	// One should verify invariants: a) val date < exp date; mktPrice & mktVol > 0,
	// but not required for this exercise.
/*	EuroTree(double mktPrice, double mktRate, double mktVol, double divRate, double strike,
		const Date& valueDate, const Date& expireDate, Porc porc, int numTimePoints,
		const DayCount& dayCount = Act365());	// Use default day count of Act/365*/

	EuroTree(double mktPrice, double mktRate, double mktVol, double divRate, double strike,
		double expiry, Porc porc, int numTimePoints);	

	double calcDelta(double shift);				// Save and restore mktPrice_ as part of this operation
	double resetMktPrice(double newMktPrice);	// Reset underlying mkt price; recalculate option price and return
	double resetMktRate(double newMktRate);		// Reset mkt risk free rate; recalculate option price and return
	double resetMktVol(double newMktVol);		// Reset mkt volatility; recalculate option price and return


	// Accessors:
	double optionPrice() const;
	Node operator()(int i, int j) const;

private:
	// Mkt Data:
	double mktPrice_, mktRate_, mktVol_;		// Market prices for underlying security, risk-free rate, and volatility

	// Product/Contract Data:
	double divRate_, strike_;	
	double expiry_;		// Time to expiration as a year fraction
	Porc porc_;			// Put or Call enum class

	// Model Settings:
	int numTimePoints_;
//	const DayCount& dayCount_;					// Stored as reference to handle polymorphic object

	// Calculated member variables:
	boost::multi_array<Node, 2> grid_;
	double dt_, u_, d_, p_;		// delta t, u, d, and p parameters, a la James book
	double discFctr_;			// Discount factor (fixed for each time step, a la James)
	double optionPrice_;		// Store result as member

	// 5th double value will be time value (replaces two dates)
	std::tuple<double, double, double, double, double, Porc, int> data_;
	
	// Helper functions:
	void calcPrice_();			// This function refactors the next five into one call
	void gridSetup_();
	void paramInit_();			// Determine delta t, u, d, and p, a la James book
	void projectPrices_();
	void calcPayoffs_();
};

#endif // !EURO_TREE_H

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


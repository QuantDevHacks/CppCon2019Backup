#ifndef EQUITY_PRICE_GENERATOR_H
#define EQUITY_PRICE_GENERATOR_H

#include <vector>

class EquityPriceGenerator
{
public:
	// A more robust approach would be to add in a stub period at beginning
	EquityPriceGenerator(double initEquityPrice, unsigned numTimeSteps, double timeToExpiry, double drift, double volatility);

	// We could also have another ctor that takes in a TermStructure object in place of a constant drift or risk free rate,
	// as well as a time path determined by a schedule based on dates and a daycount rule; viz,
	// EquityPriceGenerator(double initEquityPrice, const RealSchedule& realSchedule, const TermStructure& ts, double volatility);

	std::vector<double> operator()(int seed) const;

private:
	double dt_;
	const double initEquityPrice_;
	const int numTimeSteps_;
	const double drift_;
	const double volatility_;
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

/*
	Copyright (c) 2019, Daniel Hanson
	University of Washington
	Dept of Applied Mathematics
	Computational Finance & Risk Management (CFRM)
	For instructional purposes only
*/

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
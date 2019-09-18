#include "EquityPriceGenerator.h"
#include <random>
#include <algorithm>	
#include <ctime>
#include <cmath>

using std::vector;
using std::mt19937_64;
using std::normal_distribution;

using std::exp;

using std::vector;

EquityPriceGenerator::EquityPriceGenerator(double initEquityPrice, unsigned numTimeSteps, double timeToExpiry, double drift, double volatility) :
	initEquityPrice_(initEquityPrice), numTimeSteps_(numTimeSteps), drift_(drift), volatility_(volatility),
	dt_(timeToExpiry/numTimeSteps) {}

vector<double> EquityPriceGenerator::operator()(int seed) const
{
	vector<double> v;

	mt19937_64 mtEngine(seed);
	normal_distribution<> nd;

	auto newPrice = [this](double previousEquityPrice, double norm)
	{
		double price = 0.0;

		double expArg1 = (drift_ - ((volatility_ * volatility_) / 2.0)) * dt_;
		double expArg2 = volatility_ * norm * sqrt(dt_);
		price = previousEquityPrice * exp(expArg1 + expArg2);

		return price;
	};

	v.push_back(initEquityPrice_);				// put initial equity price into the 1st position in the vector
	double equityPrice = initEquityPrice_;

	for (int i = 1; i <= numTimeSteps_; ++i)	// i <= numTimeSteps_ since we need a price at the end of the
	{											// final time step.
		equityPrice = newPrice(equityPrice, nd(mtEngine));	// norm = nd(mtEngine)
		v.push_back(equityPrice);
	}
	
	return v;

}

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

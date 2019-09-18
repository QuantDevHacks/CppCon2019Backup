// Copyright(c) 2018, Daniel Hanson
// See license details at bottom of file

#include "../ExampleFunctionsHeader.h"


#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/bind.hpp>		// bind.hpp and ref.hpp are needed
#include <boost/ref.hpp>		// for using accumulator calculations from a std::vector

#include <vector>
#include <algorithm>

#include <iostream>

using namespace boost::accumulators;

using std::vector;
using std::for_each;
using std::move;

using std::cout;
using std::endl;

void minMaxAccumulator()
{
	cout << "*** minMaxAccumulator() ***" << endl;
	accumulator_set<double, features<tag::min, tag::max > > acc;
	// push in some data . . .
	acc(5.8);
	acc(-1.7);
	acc(2.9);
	// Display the range
	cout << '(' << extract::min(acc) << ", " << extract::max(acc) << ")\n";
	cout << endl;
}

void meanAndVarAccumulator()
{
	cout << "*** meanAndVarAccumulator() ***" << endl;
	accumulator_set<double, features<tag::mean, tag::variance > > acc;
	// push in some data . . .
	acc(1.2);
	acc(2.3);
	acc(3.4);
	acc(4.5);
	// Display the range
	cout << '(' << extract::mean(acc) << ", " << extract::variance(acc) << ")\n";
	cout << endl;
}

void vectorAndAccumulator()
{
	cout << "*** vectorAndAccumulator() ***" << endl;
	vector<double> v{ -0.7196, -3.5214 , 16.3332, 19.5379,
		2.6357, 5.1342 , -7.4481 };

	accumulator_set<double, features<tag::min, tag::max > > acc;

	// Just know this pattern; scope with boost::
	std::for_each(v.cbegin(), v.cend(), boost::bind<void>(boost::ref(acc), _1));

	// Display the range (same as before):
	cout << '(' << extract::min(acc) << ", " << extract::max(acc) << ")\n";
	cout << endl;
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

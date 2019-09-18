// Copyright(c) 2018, Daniel Hanson
// See license details at bottom of file

#include "../ExampleFunctionsHeader.h"
#include "RealFunction.h"
#include <boost/math/constants/constants.hpp>
#include <boost/math/quadrature/trapezoidal.hpp>
#include <boost/math/differentiation/finite_difference.hpp>

#include <vector>
#include <utility>
#include <future>
#include <cmath>
#include <iostream>
#include <memory>

using boost::math::quadrature::trapezoidal;
using boost::math::differentiation::finite_difference_derivative;
using boost::math::double_constants::pi;
using boost::math::double_constants::two_pi;

using std::vector;
using std::pair;
using std::make_pair;
using std::future;
using std::exp;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;


void finiteDifferences()
{
	cout << "*** finiteDifferences() ***" << endl;
	// Using a lambda:
	auto f = [](double x) {return exp(x); };

	double x = 1.7;
	double dfdx = finite_difference_derivative(f, x);

	cout << "(Using a lambda): d/dx exp(" << x << ") = " << dfdx << endl;

	// Using a function object:

	BoostQuadratic q(0.5, 1.0, 1.0);
	x = 1.0;
	double dquad = finite_difference_derivative(q, x);
	cout << "(Using a function object): d/dx (Boost)Quadratic(" << x << ") = " << dquad << endl << endl;

}

void trapezoidal()
{
	cout << "*** trapezoidal() ***" << endl;
	auto f = [](double x)
	{
		return 4.0 / (1.0 + x * x);
	};

	double appPi = trapezoidal(f, 0.0, 1.0);

	double tol = 1e-6;
	int max_refinements = 20;
	double appPi2 = trapezoidal(f, 0.0, 1.0, tol, max_refinements);

	cout << "Trapezoid Rule results for computing pi by integration" << endl;
	cout << "a) with defaults, and b) with tol and max_refine set : " << endl;
	cout << appPi << ", " << appPi2 << endl << endl;

	BoostCubic cubic(-1.0, 1.0, -1.0, 1.0);
	double cubeInt = trapezoidal(cubic, 0.0, 2.0, tol, max_refinements);
	cout << "Trapezoid Rule results for computing integral of cubic polynomial:" << endl;
	cout << cubeInt << endl << endl;

	SineFunction sf(1.0, 1.0, 0.0);
	cout << "Trapezoid Rule results for computing integral of simple" << endl;
	cout << "sine function on 0 to 2pi (note the use of the Boost two_pi constant):" << endl;
	double sineInt = trapezoidal(sf, 0.0, two_pi, tol, max_refinements);
	cout << sineInt << endl << endl;

	auto psf = make_unique<SineFunction>(1.0, 1.0, 0.0);
	cout << "Trapezoid Rule results for computing integral of simple" << endl;
	cout << "sine function on 0 to 2pi, with unique_ptr to the function:" << endl;
	double pSineInt = trapezoidal(*psf, 0.0, two_pi);
	cout << pSineInt << endl << endl;

	// NOTE:  Added the section from here to end of the function
	// AFTER original sample code was released to the class, CFRM 524 Summer 2018.
	vector<unique_ptr<RealFunction> > vfcns;
	vfcns.push_back(make_unique<SineFunction>(1.0, 1.0, 0.0)); 
	vfcns.push_back(make_unique<BoostCubic>(-1.0, 1.0, -1.0, 1.0));

//	double w = trapezoidal((*vfcns.at(0)), 0.0, two_pi);	// Not supported (trapezoidal is compile-time only)
	
	// Need to trick it with a lambda:
	cout << "Trapezoid Rule results for computing integral of simple" << endl;
	cout << "sine function on 0 to 2pi, as polymorphic function object:" << endl;
	auto g = [&vfcns](double x)
	{
		return (*vfcns.at(0))(x);
	};

	double vecUnqPtrFcn = trapezoidal(g, 0.0, two_pi);
	cout << vecUnqPtrFcn << endl << endl;
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

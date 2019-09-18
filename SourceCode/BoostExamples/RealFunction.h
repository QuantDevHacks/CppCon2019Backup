#ifndef REAL_FUNCTION_H
#define REAL_FUNCTION_H

#include <cmath>

class RealFunction
{
public:
	virtual double operator()(double x) const = 0;
	virtual double fcnValue(double x) const = 0;
	virtual ~RealFunction() = default;
};

// Classes BoostQuadratic and BoostCubic are used for the Boost
// numerical differentiation and trapezoid method integration 
// examples.  There are also quadratic and cubic function examples
// in RootFindingExamples.cpp, but these are different.  At a 
// later date, these will be consolidated.
class BoostQuadratic :public RealFunction
{
public:
	// ax^2 + bx + c
	BoostQuadratic(double a, double b, double c) :
		a_(a), b_(b), c_(c) {}

	virtual double operator()(double x) const override
	{
		return a_ * x*x + b_ * x + c_;
	}

	virtual double fcnValue(double x) const override
	{
		return x * (a_*x + b_) + c_;
	}

private:
	double a_ = 1.0, b_ = 1.0, c_ = 1.0;

};

class BoostCubic :public RealFunction	
{
public:
	// ax^3 + bx2 + cx + d
	BoostCubic(double a, double b, double c, double d) :
		a_(a), b_(b), c_(c), d_(d) {}

	virtual double operator()(double x) const override
	{
		return x*x*(a_*x + b_) + c_*x + d_;
	}

	virtual double fcnValue(double x) const override
	{
		return x*x*(a_*x + b_) + c_*x + d_;
	}

private:
	double a_, b_, c_, d_;
};

class SineFunction :public RealFunction
{
public:
	SineFunction() :a_(1.0), b_(1.0), c_(0.0) {}
	SineFunction(double a, double b, double c) :
		a_(a), b_(b), c_(c) {}

	virtual double operator()(double x) const override
	{
		return fcnValue(x);
	}

	virtual double fcnValue(double x) const override
	{
		return a_ * std::sin(b_*x + c_);
	}

private:
	double a_ = 1.0, b_ = 1.0, c_ = 1.0;

};


#endif // !REAL_FUNCTION_H

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


// Copyright(c) 2018, Daniel Hanson
// See license details at bottom of file

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
Copyright (c) 2018, Daniel Hanson
CFRM 524, University of Washington
For instructional purposes only

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

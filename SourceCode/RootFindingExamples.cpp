#include "ExampleFunctionsHeader.h"
#include "RootFinding/Bisection.h"
#include "RootFinding/Steffenson.h"
#include <cmath>
#include <iostream>

using qdh::root_finding::bisection;
using qdh::root_finding::steffensonMethod;
using qdh::root_finding::Real;		// typedef for double
using std::log;
using std::cout;
using std::endl;

void bisectionExamples()
{
	cout << endl << "*** bisectionExamples() ***" << endl;
	// First, represent functions as function objects:
	Quadratic qdr;
	SineFcn sf;

	auto qdrRoot = bisection(qdr, -3.0, -1.5, 0.0001, 1000);
	auto sinRoot = bisection(sf, -1.0, 3.0);

	cout << "Passing function objects:" << endl;
	cout << "Root of quadratic function = " << qdrRoot << endl;
	cout << "Root of sine function = " << sinRoot << endl << endl;

	// Passing function objects // (both OK):
	// Root of quadratic function = -2
	// Root of sine function = 1.52815e-162 -- essentially zero

	// Next, use lambdas:
	auto cubic = [](double x) {return x * x * x + 1; };	//, -10.0, 0.0)
	auto powSeven = [](double x) {return std::pow(x, 7.0); };	// , -3.0, 3.0)

	auto cubicRoot = bisection(cubic, -10.0, 3.0, 0.0001, 1000);
	// Put in larger tolerance and fewer max iterations, to demonstrate:
	auto powRoot = bisection(powSeven, -3.0, 3.0, 0.0001, 100);
	cout << "Passing lambda expressions:" << endl;
	cout << "Root of cubic function = " << cubicRoot << endl;
	cout << "Root of power function = " << powRoot << endl << endl;

	// Passing lambda expressions // (both OK):
	// Root of cubic function = -1
	// Root of power function = 7.44402e-24 -- essentially zero
}

void steffensonExamples()
{
	cout << endl << "*** steffensonExamples() ***" << endl;
	// First, represent functions as function objects:
	Quadratic qdr;
	SineFcn sf;

	auto qdrRoot = steffensonMethod(qdr, -1.5);
	auto sinRoot = steffensonMethod(sf, -0.5);

	cout << "Passing function objects:" << endl;
	cout << "Root of quadratic function = " << qdrRoot << endl;
	cout << "Root of sine function = " << sinRoot << endl << endl;

	// Passing function objects // (both OK):
	// Root of quadratic function = -2
	// Root of sine function = 1.52815e-162 -- essentially zero

	// Next, use lambdas:
	auto cubic = [](double x) {return x * x * x + 1; };	//, -10.0, 0.0)
	auto logFcn = [](double x) {return log(x - 3.5); };	// , -3.0, 3.0)

	auto cubRoot = steffensonMethod(cubic, -10.0);
	// Put in larger tolerance and fewer max iterations, to demonstrate:
	auto logRoot = steffensonMethod(logFcn, 5.0, 0.001, 1000000);
	cout << "Passing lambda expressions:" << endl;
	cout << "Root of cubic function = " << cubRoot << endl;
	cout << "Root of log function = " << logRoot << endl << endl;

	// Passing lambda expressions :		// Both OK
	// Root of cubic function = -1
	// Root of log function = 4.5

}

// Class member functions below:
double Quadratic::operator()(double x) const
{
	return x * (x + 3.0) + 2.0;
}

double SineFcn::operator()(double x) const
{
	return sin(x);
}


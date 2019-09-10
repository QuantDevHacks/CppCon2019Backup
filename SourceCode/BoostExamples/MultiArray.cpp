#include "../ExampleFunctionsHeader.h"
#include "TestClassForMultiArray.h"
#include "EuroTree.h"

#include <boost/multi_array.hpp>
#include <algorithm>
#include <iostream>

void TestLattice()
{
	std::cout << std::endl << "***** multi_array: TestLattice() *****" << std::endl;
	// boost::extents in 2D represent number of rows and columns 
	// in the generic matrix; ie, extents[numRows][numCols].
	boost::multi_array<TestClassForMultiArray, 2> mtx(boost::extents[4][6]);

	// 1st quick test:  compiles and runs OK
	mtx[0][0].calc(3.0, 4.0);

	// Populate the old fashioned way with a loop.
	// Use the mutator calc(double, double) to 
	// set each element.  Note: the shape() method
	// on boost::multi_array gives us access to the
	// bounds on each dimension (rows and columns 
	// (in the 2D matrix case).
	for (auto i = 0; i < mtx.shape()[0]; ++i)
	{
		for (auto j = 0; j < mtx.shape()[1]; ++j)
		{
			mtx[i][j].calc(static_cast<double>(i), static_cast<double>(j));
		}
	}

	// Verify element type (TestClass):
	std::cout << mtx[1][1]() << " " << typeid(mtx[1][1]).name() << std::endl << std::endl;

	// Use to print each element:
	auto print = [](const TestClassForMultiArray& tc)
	{
		// Function object returns real value stored on object:
		std::cout << tc() << " ";
	};

	// Display all elements, in one row, buy using std::for_each(.):
	std::for_each(mtx.data(), mtx.data() + mtx.num_elements(), print);

	std::cout << std::endl << std::endl;
}

void eurology()
{
	std::cout << std::endl << "***** multi_array: eurology() (Lattice option pricer) *****" << std::endl;
	EuroTree myTree(100.0, 0.10, 0.2, 0.04, 100.0,
		0.5, Porc::CALL, 4);


	std::cout << std::endl << std::endl;

	std::cout << "Display terminal underlying and payoff prices:" << std::endl;
	for (int i = 3; i >= 0; --i)
	{
		std::cout << i << ": " << myTree(i, 3).underlying << ", " << myTree(i, 3).payoff << std::endl;
	}

}
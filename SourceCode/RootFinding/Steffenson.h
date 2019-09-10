/*
	Copyright (c) 2019, Daniel Hanson, Tania Luo
	University of Washington
	Dept of Applied Mathematics
	Computational Finance & Risk Management (CFRM)
	For instructional purposes only
*/

#ifndef STEFFENSON_H
#define STEFFENSON_H

#include <cmath>
#include <limits>

namespace qdh 
{
	namespace root_finding 
	{
		using Real = double;

		template<class F>
		auto steffensonMethod(F f, Real initialGuess, Real tol = std::sqrt(std::numeric_limits<Real>::epsilon()), unsigned int maxIterations = 100000, 
			Real guessZero = std::sqrt(std::numeric_limits<Real>::epsilon()))
		{
			//We first check to see if the initial guess is already a root of the target function
			if (std::abs(f(initialGuess)) < guessZero)
			{
				return initialGuess;
			}

			Real x_n_1 = initialGuess;
			Real x_n = 0.0;

			for (unsigned int i = 0; i < maxIterations; ++i)
			{
				//Formula for Steffensen's method from An Introduction to Numerical Analysis, 2nd ed., Atkinson 1989
				Real D = f(x_n_1 + f(x_n_1)) - f(x_n_1);
				x_n = x_n_1 - ((f(x_n_1)*f(x_n_1)) / D);
				if (std::abs(x_n_1 - x_n) < tol)
				{
					return x_n;
				}
				x_n_1 = x_n;
			}

//			return x_n;
			return std::numeric_limits<Real>::infinity();
		}
	} 
}

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

#endif // !STEFFENSON_H


/*
	Copyright (c) 2019, Daniel Hanson, Tania Luo
	University of Washington
	Dept of Applied Mathematics
	Computational Finance & Risk Management (CFRM)
	For instructional purposes only
*/

#ifndef BISECTION_H
#define BISECTION_H

#include <cmath>
#include <limits>

namespace qdh {
	namespace root_finding {

		using Real = double;

		template<class F>
		auto bisection(F f, Real a, Real b, Real tol = std::sqrt(std::numeric_limits<Real>::epsilon()),
			unsigned int maxIterations = 1000, Real guessZero = std::sqrt(std::numeric_limits<Real>::epsilon()))
		{
			//Check that the two inital guesses are not zeroes already
			if (std::abs(f(a)) < guessZero)
			{
				return a;
			}
			if (std::abs(f(b)) < guessZero)
			{
				return b;
			}
			if (f(b) * f(a) > 0)
			{
				// Error condition; must have f(b) * f(a) < 0; 
				// otherwise, does not converge:
				return std::numeric_limits<Real>::infinity();
			}
			// Algorithm for bisection method adapted from Numerical Analysis, 5th Edition, Burden and Faires, 1993
			// and An Introduction to Numerical Analysis, 2nd Eidtion, K. Atkinson, 1989
			for (unsigned int i = 0; i < maxIterations; ++i)
			{
				Real c = (a + b) / 2;
				if ((std::abs(b-c)/std::abs(b)) < tol)
				{
					return c;
				}

				if (f(b) * f(c) <= 0)
				{
					a = c;
				}
				else
				{
					b = c;
				}
			}
			// Error condition: does not converge:
			return std::numeric_limits<Real>::infinity();
		}
} }

#endif // !BISECTION_H

/*
	Copyright 2019 Daniel Hanson, Tania Luo

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

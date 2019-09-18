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

			return std::numeric_limits<Real>::infinity();
		}
	} 
}

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


#endif // !STEFFENSON_H


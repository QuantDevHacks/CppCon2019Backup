#ifndef	EXAMPLE_FUNCTIONS_HEADER_H
#define EXAMPLE_FUNCTIONS_HEADER_H

// --- Root finding examples ---
void bisectionExamples();
void steffensonExamples();


class Quadratic
{
public:
	double operator()(double x) const;
};

class SineFcn
{
public:
	double operator()(double x) const;
};


// --- Boost examples ---
// Differentiation
void finiteDifferences();

// Integration
void trapezoidal();

// Circular Buffers
void simple_example();
void time_series_example();

// Accumulators
void minMaxAccumulator();
void meanAndVarAccumulator();
void vectorAndAccumulator();

// MultiArray
void TestLattice();
void eurology();	// Binary lattice option pricing


#endif

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


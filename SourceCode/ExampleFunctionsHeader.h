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

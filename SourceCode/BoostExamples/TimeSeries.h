#ifndef TIME_SERIES_H
#define TIME_SERIES_H

#include <boost/circular_buffer.hpp>
#include <vector>
using Unsigned = size_t;

class TimeSeries
{
public:
	TimeSeries(Unsigned length);
	TimeSeries(const boost::circular_buffer<double>& ts);
	TimeSeries(const std::vector<double>& ts);
	void append(double x);
	double value(Unsigned k) const;
	double movingAverage(Unsigned t = 0) const;
	double volatility(Unsigned t = 0) const;		// Exercise
	boost::circular_buffer<double> buffer() const;

private:
	boost::circular_buffer<double> ts_;
	double mean_(Unsigned t = 0) const;
};

#endif